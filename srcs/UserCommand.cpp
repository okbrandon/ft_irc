/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:02:05 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/05 11:04:57 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/UserCommand.hpp"

UserCommand::UserCommand(void) : ACommand("USER") {}

UserCommand::~UserCommand(void) {}

std::string	UserCommand::_extractRealname(std::deque<std::string> args) const {
	std::string	realname;

	for (size_t i = 4; i < args.size(); i++) {
		realname.append(args.at(i));
		
		if (i < args.size() - 1)
			realname.append(" ");
	}
	if (realname.at(0) == ':')
		realname.erase(0, 1);
	return (realname);
}

void	UserCommand::execute(void) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	std::string	username;
	std::string	realname;

	if (!this->_user->hasSentPassword())
		throw ENTER_PASS_FIRST;
	if (this->_args.size() < 5)
		throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);
	if (this->_user->isRegistered())
		throw ERR_ALREADYREGISTRED(userId, this->_user->getNickname());
	
	username = this->_args[1];
	realname = this->_extractRealname(this->_args);
	this->_user->setUsername(username);
	this->_user->setRealname(realname);
	this->_user->addSendBuffer(": You are now known as ");
	this->_user->addSendBuffer(BCYN + username + CRESET + " (" + BCYN + realname + CRESET + ")\r\n");
}
