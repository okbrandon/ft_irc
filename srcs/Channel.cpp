/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:52:44 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/01 10:02:54 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

/* Constructors & Destructors */
Channel::Channel(void) {}

Channel::Channel(std::string name) {
	this->_name = name;
	this->_key = "";
}

Channel::Channel(Channel const &origin) {
	*this = origin;
}

Channel::~Channel(void) {
	this->_users.clear();
	this->_operators.clear();
	this->_modes.clear();
	this->_conversation.clear();
}

/* Functions */
void	Channel::addMode(char mode) {
	if (std::find(this->_modes.begin(), this->_modes.end(), mode) != this->_modes.end())
		return ;
	this->_modes.push_back(mode);
}

void	Channel::removeMode(char mode) {
	if (std::find(this->_modes.begin(), this->_modes.end(), mode) == this->_modes.end())
		return ;
	for (std::vector<char>::iterator it = this->_modes.begin(); it != this->_modes.end(); it++) {
		if (*it == mode) {
			this->_modes.erase(it);
			return ;
		}
	}
}

void	Channel::addUser(User *user) {
	if (std::find(this->_users.begin(), this->_users.end(), user) != this->_users.end())
		return ;
	this->_users.push_back(user);
}

void	Channel::removeUser(User *user) {
	if (std::find(this->_users.begin(), this->_users.end(), user) == this->_users.end())
		return ;
	for (std::vector<User*>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
		if (*it == user) {
			this->_users.erase(it);
			return ;
		}
	}
}

void	Channel::addOperator(User *user) {
	if (std::find(this->_operators.begin(), this->_operators.end(), user) != this->_operators.end())
		return ;
	this->_operators.push_back(user);
}

void	Channel::removeOperator(User *user) {
	if (std::find(this->_operators.begin(), this->_operators.end(), user) == this->_operators.end())
		return ;
	for (std::vector<User*>::iterator it = this->_operators.begin(); it != this->_operators.end(); it++) {
		if (*it == user) {
			this->_operators.erase(it);
			return ;
		}
	}
}

void	Channel::broadcast(std::string message) {
	for (std::vector<User*>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
		User	*user = *it;

		// adding message to user send buffer
		user->addSendBuffer(message);
	}
}

void	Channel::excludeBroadcast(std::string message, User *excluded) {
	for (std::vector<User*>::iterator it = this->_users.begin(); it != this->_users.end(); it++) {
		User	*user = *it;

		if (!user->getNickname().compare(excluded->getNickname()))
			continue ;
		// adding message to user send buffer
		user->addSendBuffer(message);
	}
}

/* Getters */
std::string	Channel::getKey(void) const {
	return (this->_key);
}

std::string	Channel::getName(void) const {
	return (this->_name);
}

std::string	Channel::getTopic(void) const {
	return (this->_topic);
}

std::vector<char>	Channel::getModes(void) const {
	return (this->_modes);
}

std::vector<User*>	Channel::getUsers(void) const {
	return (this->_users);
}

std::vector<User*>	Channel::getOperators(void) const {
	return (this->_operators);
}

std::vector<std::string>	Channel::getConversation(void) const {
	return (this->_conversation);
}

unsigned int	Channel::getLimit() const {
	return (this->_limit);
}

User	*Channel::getOwner(void) const {
	return (this->_owner);
}

bool	Channel::isOperator(User *user) {
	if (std::find(this->_operators.begin(), this->_operators.end(), user) != this->_operators.end())
		return (true);
	return (false);
}

bool	Channel::isInChannel(User *user) {
	if (std::find(this->_users.begin(), this->_users.end(), user) != this->_users.end())
		return (true);
	return (false);
}

bool	Channel::isKeyProtected(void) const {
	return (!this->_key.empty());
}

bool	Channel::hasMode(char mode) const {
	return (std::find(this->_modes.begin(), this->_modes.end(), mode) != this->_modes.end());
}

/* Setters */
void	Channel::setKey(std::string key) {
	this->_key = key;
}

void	Channel::setTopic(std::string topic) {
	this->_topic = topic;
}

void	Channel::setLimit(unsigned int limit) {
	this->_limit = limit;
}

void	Channel::setOwner(User *owner) {
	this->_owner = owner;
}

/* Overloaded operators */
Channel	&Channel::operator=(Channel const &origin) {
	this->_name = origin._name;
	this->_topic = origin._topic;
	this->_modes = origin._modes;
	this->_users = origin._users;
	this->_operators = origin._operators;
	this->_conversation = origin._conversation;
	this->_limit = origin._limit;
	this->_owner = origin._owner;
	return (*this);
}
