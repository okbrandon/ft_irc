/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:49:41 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 17:56:56 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/commands/PassCommand.hpp"

PassCommand::PassCommand(void) : ACommand("PASS") {}

PassCommand::~PassCommand(void) {}

void	PassCommand::execute(void) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());

	if (this->_user->hasSentPassword())
		throw ERR_ALREADYREGISTRED(userId, this->_user->getNickname());
	if (this->_args.size() < 2)
		throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);
	if (this->_args[1].compare(this->_server->getPassword()))
		throw ERR_PASSWDMISMATCH(userId, this->_user->getNickname());
	
	this->_user->setSentPassword(true);
	this->_user->addSendBuffer(": Password is correct, you may now identify yourself with ");
	this->_user->addSendBuffer(BCYN "USER" CRESET " and " BCYN "NICK" CRESET " commands if you haven't already.\r\n");
}
