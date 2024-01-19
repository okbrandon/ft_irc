/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:45:46 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/01/19 17:48:12 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

/* Constructors & Destructors */
User::User(void) {}

User::User(std::string &host, int port, int socket) {
	this->_host = host;
	this->_nickname = "";
	this->_username = "";
	this->_port = port;
	this->_socket = socket;
	this->_registered = false;
	this->_sentPassword = false;
}

User::User(User const &origin) {
	this->_host = origin.getHost();
	this->_nickname = origin.getNickname();
	this->_username = origin.getUsername();
	this->_port = origin.getPort();
	this->_socket = origin.getSocket();
	this->_registered = origin.isRegistered();
	this->_sentPassword = origin.hasSentPassword();
}

User::~User(void) {}

/* Functions */
void	User::tryRegister(void) {
	if (!this->_sentPassword || this->_nickname.empty() || this->_username.empty())
		return ;
	this->_registered = true;
	this->sendMessage("Welcome stoopid user");
}

void	User::sendMessage(std::string message) {
	message = message.append("\r\n");
	send(this->_socket, message.c_str(), message.size(), 0);
}

/* Getters & Setters */
std::string	User::getHost(void) const {
	return (this->_host);
}

std::string	User::getNickname(void) const {
	return (this->_nickname);
}

std::string	User::getUsername(void) const {
	return (this->_username);
}

int	User::getPort(void) const {
	return (this->_port);
}

int	User::getSocket(void) const {
	return (this->_socket);
}

bool	User::isRegistered(void) const {
	return (this->_registered);
}

bool	User::hasSentPassword(void) const {
	return (this->_sentPassword);
}

void	User::setNickname(std::string &nickname) {
	this->_nickname = nickname;
}

void	User::setUsername(std::string &username) {
	this->_username = username;
}

/* Overloaded operators */
User	&User::operator=(User const &origin) {
	this->_host = origin.getHost();
	this->_nickname = origin.getNickname();
	this->_username = origin.getUsername();
	this->_port = origin.getPort();
	this->_socket = origin.getSocket();
	this->_registered = origin.isRegistered();
	this->_sentPassword = origin.hasSentPassword();
	return (*this);
}