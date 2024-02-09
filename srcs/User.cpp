/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:45:46 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/09 16:19:16 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

/* Constructors & Destructors */
User::User(void) {}

User::User(std::string &host, int port, int socket) {
	this->_host = host;
	this->_nickname = "";
	this->_username = "";
	this->_realname = "";
	this->_readBuffer = "";
	this->_port = port;
	this->_socket = socket;
	this->_registered = false;
	this->_sentPassword = false;
}

User::User(User const &origin) {
	this->_host = origin.getHost();
	this->_nickname = origin.getNickname();
	this->_username = origin.getUsername();
	this->_realname = origin.getRealname();
	this->_readBuffer = origin.getReadBuffer();
	this->_port = origin.getPort();
	this->_socket = origin.getSocket();
	this->_registered = origin.isRegistered();
	this->_sentPassword = origin.hasSentPassword();
}

User::~User(void) {}

/* Functions */
void	User::tryRegister(Server *server) {
	if (this->_registered)
		return ;
	if (!this->_sentPassword || this->_nickname.empty() || this->_username.empty() || this->_realname.empty())
		return ;
	this->_registered = true;
	this->sendDirectMessage("CAP * LS :multi-prefix sasl");
	this->addSendBuffer(RPL_WELCOME(this->_nickname, USER_IDENTIFIER(this->_nickname, this->_username)));
	this->addSendBuffer(RPL_YOURHOST(this->_nickname, "42FT_IRC", "1.0"));
	this->addSendBuffer(RPL_CREATED(this->_nickname, server->getCreationDate()));
	(void) server; // voiding because compiler is dumb
}

void	User::sendBufferMessage(void) {
	std::istringstream	buffer(this->_sendBuffer);

	if (this->_sendBuffer.size() == 0)
		return ;
	if (send(this->_socket, this->_sendBuffer.c_str(), this->_sendBuffer.size(), 0) < 0)
		throw std::runtime_error("Cannot send bytes to user");
	this->_sendBuffer.clear();
}

void	User::sendDirectMessage(std::string message) {
	message = message.append("\r\n");
	std::cout << Utils::toString(USER_INFO) << BRED "[WARN] " CRESET "Sending direct message to " << this->_socket << std::endl;
	if (send(this->_socket, message.c_str(), message.size(), 0) < 0)
		throw std::runtime_error("Cannot send bytes to user");
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

std::string	User::getRealname(void) const {
	return (this->_realname);
}

std::string	User::getReadBuffer(void) const {
	return (this->_readBuffer);
}

std::string	User::getSendBuffer(void) const {
	return (this->_sendBuffer);
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

void	User::setNickname(std::string const &nickname) {
	this->_nickname = nickname;
}

void	User::setUsername(std::string const &username) {
	this->_username = username;
}

void	User::setRealname(std::string const &realname) {
	this->_realname = realname;
}

void	User::setSentPassword(bool didSend) {
	this->_sentPassword = didSend;
}

void	User::setReadBuffer(std::string const &buffer) {
	this->_readBuffer = buffer;
}

void	User::setSendBuffer(std::string const &buffer) {
	this->_sendBuffer = buffer;
}

void	User::addSendBuffer(std::string buffer) {
	this->_sendBuffer += buffer;
}

/* Overloaded operators */
User	&User::operator=(User const &origin) {
	this->_host = origin.getHost();
	this->_nickname = origin.getNickname();
	this->_username = origin.getUsername();
	this->_realname = origin.getRealname();
	this->_readBuffer = origin.getReadBuffer();
	this->_port = origin.getPort();
	this->_socket = origin.getSocket();
	this->_registered = origin.isRegistered();
	this->_sentPassword = origin.hasSentPassword();
	return (*this);
}
