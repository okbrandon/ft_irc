/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:52:26 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/01/16 17:37:32 by bsoubaig         ###   ########.fr       */
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

/* Functions */
void	Server::run(void) {
	std::vector<pollfd>::iterator	it;
	pollfd	newPoll = {this->_listenerSocket, POLLIN, 0};

	if (fcntl(this->_listenerSocket, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("Cannot manipulate fd");
	this->_polls.push_back(newPoll);
	std::cout << "Server is ready!" << std::endl;
	while ("please work server") {
		it = this->_polls.begin();
		int	pollCount = poll(&(*it), this->_polls.size(), -1);

		if (pollCount < 0)
			throw std::runtime_error("Impossible to wait for some event");
		while (it != this->_polls.end()) {
			if (it->revents & POLLIN) {
				if (it->fd == this->_listenerSocket) {
					// handle new client
				} else {
					// handle client request
				}
			}
			++it;
		}
	}
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