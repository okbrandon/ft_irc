/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:30:16 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/27 16:15:57 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ACommand.hpp"

ACommand::ACommand(void) {}

ACommand::ACommand(std::string name) {
	this->_name = name;
	this->_aliases = std::deque<std::string>();
	this->_calledCommand = "";
	this->_user = NULL;
	this->_server = NULL;
}

ACommand::ACommand(ACommand const &origin) {
	*this = origin;
}

ACommand::~ACommand(void) {
	while (!this->_args.empty())
		this->_args.erase(this->_args.begin());
	while (!this->_aliases.empty())
		this->_aliases.erase(this->_aliases.begin());
	this->_args.clear();
	this->_aliases.clear();
}

std::string	ACommand::getName(void) const {
	return (this->_name);
}

std::string	ACommand::getCalledCommand(void) const {
	return (this->_calledCommand);
}

std::deque<std::string>	ACommand::getAliases(void) const {
	return (this->_aliases);
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

void	ACommand::setCalledCommand(std::string calledCommand) {
	this->_calledCommand = calledCommand;
}

void	ACommand::addAliase(std::string aliase) {
	this->_aliases.push_back(aliase);
}

bool	ACommand::hasAliase(std::string aliase) const {
	if (std::find(this->_aliases.begin(), this->_aliases.end(), aliase) == this->_aliases.end())
		return (false);
	return (true);
}

ACommand	&ACommand::operator=(ACommand const &origin) {
	this->_name = origin._name;
	this->_aliases = origin._aliases;
	this->_args = origin._args;
	this->_calledCommand = origin._calledCommand;
	this->_user = origin._user;
	this->_server = origin._server;
	return (*this);
}
