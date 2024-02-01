/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:52:26 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/01 17:17:58 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

/* Constructors & Destructors */
Server::Server(void) {}

Server::Server(const std::string &hostname, int port, const std::string &password) {
	this->_creationDate = _createTimestamp();
	this->_hostname = hostname;
	this->_port = port;
	this->_password = password;
	this->_polls.reserve(MAX_CONNECTIONS);
	this->_listenerSocket = _createSocket();
}

Server::Server(const Server &origin) {
	*this = origin;
}

Server::~Server(void) {
	g_server_running = false;
}

/* Private functions */
std::string	Server::_createTimestamp(void) {
	time_t		time = std::time(0);
	struct tm	*localTime = localtime(&time);
	char		buffer[80]; // format string

	strftime(buffer, 80, "%a %b %d, %H:%M:%S UTC", localTime);
	return (Utils::toString(buffer));
}

int	Server::_createSocket(void) {
	struct sockaddr_in	serverAddr; // using sockaddr_in for IPv4 only
	int					sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0)
		throw std::runtime_error("Cannot open socket");
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY; // equivalent to 0.0.0.0
	serverAddr.sin_port = htons(this->_port);

	if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
		throw std::runtime_error("Cannot bind socket");
	if (listen(sock, MAX_CONNECTIONS) < 0)
		throw std::runtime_error("Listen failed");
	return (sock);
}

bool	Server::_createUserConnection(void) {
	struct sockaddr_in	userAddr;
	socklen_t			userAddrLen = sizeof(userAddr);
	int					userSocket = accept(this->_listenerSocket, (sockaddr *)&userAddr, &userAddrLen);

	if (userSocket < 0) {
		// Failure with accept() but still running server loop
		return (false);
	}
	if (this->_polls.size() - 1 >= MAX_CONNECTIONS) {
		// Server is full, should send a message to user before kicking
		close(userSocket);
	} else {
		this->_addUser(userSocket, userAddr);
	}
	return (true);
}

bool	Server::_handleUserConnection(std::vector<pollfd>::iterator &it) {
	User		*user = findUserByFd(it->fd);
	std::string	delimiter = "\r\n";
	std::string	message;
	char		buffer[4096];
	int			read;

	memset(buffer, 0, sizeof(buffer));
	read = recv(it->fd, buffer, 4096, 0);
	if (read < 0) {
		std::cerr << Utils::toString(SERVER_PREFIX) << CRESET "An error occurred with recv(), ignoring..." CRESET << std::endl;
		this->_removeUser(it->fd, it);
		return (false);
	}
	if (read == 0) {
		// User disconnected
		std::cout << Utils::toString(SERVER_PREFIX) << "Disconnection event fired!" << std::endl;
		this->_removeUser(it->fd, it);
		return (false);
	}
	message = Utils::toString(buffer);
	message.replace(message.find("\n"), delimiter.size(), delimiter);
	std::cout << Utils::toString(SERVER_PREFIX) << "From " << it->fd << ": '" << message << "'" << std::endl;
	// Should handle commands from here
	user->setReadBuffer(message);
	this->_parseReceived(it->fd, user->getReadBuffer()); // command handler inside this function
	return (true);
}

bool	Server::_handlePollOut(std::vector<pollfd>::iterator &it) {
	User	*user = findUserByFd(it->fd);

	if (!user) // no connection established, skipping
		return (true);
	user->sendBufferMessage();
	return (true);
}

void	Server::_addUser(int userSocket, struct sockaddr_in userAddr) {
	pollfd		userPoll;
	std::string	userHost = Utils::toString(inet_ntoa(userAddr.sin_addr));
	User		userObj(userHost, ntohs(userAddr.sin_port), userSocket);

	userPoll.fd = userSocket;
	userPoll.events = POLLIN | POLLOUT;
	this->_polls.push_back(userPoll);
	this->_users.insert(std::pair<int, User>(userSocket, userObj));
	std::cout << Utils::toString(SERVER_PREFIX) << "New client with id " << userSocket << "..." << std::endl;
}

void	Server::_removeUser(int currentFd, std::vector<pollfd>::iterator &it) {
	if (close(currentFd) < 0)
		std::cerr << Utils::toString(SERVER_PREFIX) << BRED "close() error when removing user, continue..." CRESET << std::endl;
	this->_users.erase(currentFd);
	this->_polls.erase(it);
	std::cout << Utils::toString(SERVER_PREFIX) << "Bye client with id " << currentFd << "." << std::endl;
}

void	Server::_parseReceived(int fd, std::string message) {
	std::vector<std::string>	commands;
	User	*user = findUserByFd(fd);

	if (message.find("\r\n") != std::string::npos) {
		commands = Utils::getSplittedMessage(message);

		for (size_t i = 0; i != commands.size(); i++) {
			if (user->isRegistered())
				continue; // should exec other commands
			user->tryRegister(this);
			std::cout << Utils::toString(SERVER_PREFIX) << "Potential command '" << commands[i] << "'" << std::endl;
		}
	}
	if (user->getReadBuffer().find("\r\n"))
		user->getReadBuffer().clear();
}

/* Functions */
void	Server::run(void) {
	pollfd	serverPoll = {
		this->_listenerSocket, // specifies the file descriptor to monitor
		POLLIN | POLLOUT, // Data available to read & Writing now will not block
		0 // indicate which of those events actually occurred
	};

	if (fcntl(this->_listenerSocket, F_SETFL, O_NONBLOCK) < 0) // non-blocking socket
		throw std::runtime_error("Cannot manipulate fd");
	this->_polls.push_back(serverPoll);
	g_server_running = true;
	std::cout << Utils::toString(SERVER_PREFIX) << "Ready to welcome users!" << std::endl;
	while (g_server_running) {
		std::vector<pollfd>::iterator	it = this->_polls.begin();
		int pollCount = poll(&(*it), this->_polls.size(), -1);

		if (g_server_running && pollCount < 0)
			throw std::runtime_error("Impossible to wait for some event");
		while (it != this->_polls.end()) {
			if (it->revents & POLLIN) {
				if (it->fd == this->_listenerSocket) {
					if (!this->_createUserConnection())
						continue ; // skipping if accept() fails
				} else {
					if (!this->_handleUserConnection(it))
						break ;
				}
			}
			else if (it->revents & POLLOUT) {
				if (!this->_handlePollOut(it))
					break ;
			}
			++it;
		}
	}
	std::cout << Utils::toString(SERVER_PREFIX) << "Server is shutting down..." << std::endl;
}

User	*Server::findUserByFd(int fd) {
	std::map<int, User>::iterator	it = this->_users.find(fd);

	if (it == this->_users.end())
		return (NULL);
	return (&it->second);
}

/* Getters & Setters */
std::string	Server::getCreationDate(void) const {
	return (this->_creationDate);
}

std::string	Server::getHostname(void) const {
	return (this->_hostname);
}

std::string	Server::getPassword(void) const {
	return (this->_password);
}

int	Server::getPort(void) const {
	return (this->_port);
}

int	Server::getListenerSocket(void) const {
	return (this->_listenerSocket);
}

/* Overloaded operators */
Server	&Server::operator=(const Server &origin) {
	(void) origin; // should complete this
	return (*this);
}