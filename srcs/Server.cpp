/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:52:26 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/01/19 17:47:34 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

/* Constructors & Destructors */
Server::Server(void) {}

Server::Server(const std::string &hostname, int port, const std::string &password) {
	this->_hostname = hostname;
	this->_port = port;
	this->_password = password;
	this->_polls.reserve(MAX_CONNECTIONS);
	this->_listenerSocket = _createSocket();

	std::cout << "[Server] New object." << std::endl;
}

Server::Server(const Server &origin) {
	*this = origin;
}

Server::~Server(void) {
	std::cout << "[Server] Deleted object." << std::endl;
}

/* Private functions */
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
	char	message[4096];
	int		read;

	memset(message, 0, sizeof(message));
	read = recv(it->fd, message, 4096, 0);
	if (read < 0) {
		std::cout << "ASS" << std::endl;
		this->_removeUser(it->fd, it);
		return (false);
	}
	if (read == 0) {
		// User disconnected
		std::cout << "[Server] Disconnection event fired!" << std::endl;
		this->_removeUser(it->fd, it);
		return (false);
	}
	std::cout << "[Server] From " << it->fd << ": " << Utils::toString(message) << std::endl;
	// Should handle commands from here
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
	std::cout << "[Server] New client with id " << userSocket << "..." << std::endl;
}

void	Server::_removeUser(int currentFd, std::vector<pollfd>::iterator &it) {
	if (close(currentFd) < 0)
		std::cerr << "[Server] close() error when removing user, continue..." << std::endl;
	this->_users.erase(currentFd);
	this->_polls.erase(it);
	std::cout << "[Server] Bye client with id " << currentFd << "." << std::endl;
}

/* Functions */
void	Server::run(void) {
	pollfd	serverPoll = {this->_listenerSocket, POLLIN, 0};

	if (fcntl(this->_listenerSocket, F_SETFL, O_NONBLOCK) < 0) // macOS?
		throw std::runtime_error("Cannot manipulate fd");
	this->_polls.push_back(serverPoll);
	std::cout << "Server is ready!" << std::endl;
	while ("please work server") { // should probably use a boolean
		std::vector<pollfd>				tempPolls;
		std::vector<pollfd>::iterator	it = this->_polls.begin();
		int								pollCount = poll(&(*it), this->_polls.size(), -1);

		if (pollCount < 0)
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
			++it;
		}
		this->_polls.insert(this->_polls.end(), tempPolls.begin(), tempPolls.end());
	}
}

User	*Server::findUserByFd(int fd) {
	std::map<int, User>::iterator	it = this->_users.find(fd);

	if (it == this->_users.end())
		return (NULL);
	return (&it->second);
}

/* Getters & Setters */
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
	(void) origin;
	return (*this);
}