/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:30:16 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/07 17:06:52 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ACommand.hpp"

ACommand::ACommand(void) {}

ACommand::ACommand(std::string name) {
	this->_name = name;
	this->_user = NULL;
	this->_server = NULL;
}

ACommand::ACommand(ACommand const &origin) {
	*this = origin;
}

ACommand::~ACommand(void) {
	while (!this->_args.empty())
		this->_args.erase(this->_args.begin());
	this->_args.clear();
}

std::string	ACommand::getName(void) const {
	return (this->_name);
}

void	ACommand::setArgs(std::deque<std::string> args) {
	this->_args = args;
}

void	ACommand::setUser(User *user) {
	this->_user = user;
}

void	ACommand::setServer(Server *server) {
	this->_server = server;
}

ACommand	&ACommand::operator=(ACommand const &origin) {
	this->_name = origin._name;
	this->_args = origin._args;
	this->_user = origin._user;
	this->_server = origin._server;
	return (*this);
}
