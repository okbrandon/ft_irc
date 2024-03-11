/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:13 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/11 17:56:45 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/commands/InviteCommand.hpp"

InviteCommand::InviteCommand(void) : ACommand("INVITE") {}

InviteCommand::~InviteCommand(void) {}

void	InviteCommand::execute(void) const {
	std::string userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());

	if (this->_args.size() < 3)
		throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);

	User		*target = this->_server->findUserByName(this->_args[1]);
	Channel		*channel = this->_server->findChannelByName(this->_args[2]);

	if (!target)
		throw ERR_NOSUCHNICK(userId, this->_user->getNickname(), this->_args[1]);

	if (!channel) { // channel is inexistant, creating one
		Channel *newChannel = new Channel(this->_args[2]);
		newChannel->setOwner(this->_user);
		newChannel->addOperator(this->_user);
		newChannel->addUser(this->_user);
		this->_server->addChannel(newChannel);
		channel = newChannel;
	}
	if (!channel->isInChannel(this->_user))
		throw ERR_NOTONCHANNEL(userId, this->_user->getNickname(), channel->getName());
	if (channel->hasMode('i') && !channel->isOperator(this->_user))
		throw ERR_CHANOPRIVSNEEDED(userId, this->_user->getNickname(), this->_args[2]);

	if (!channel->isInChannel(target)) {
		std::string	response = userId + " INVITE " + target->getNickname() + " " + channel->getName() + "\r\n";

		target->addSendBuffer(response);
		this->_user->addSendBuffer(RPL_INVITING(userId, this->_user->getNickname(), channel->getName(), target->getNickname()));
		channel->addUser(target);
	}
}
