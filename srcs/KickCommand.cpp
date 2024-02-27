/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:24 by evmorvan          #+#    #+#             */
/*   Updated: 2024/02/27 13:56:47 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/KickCommand.hpp"

KickCommand::KickCommand(void) : ACommand("KICK") {}

KickCommand::~KickCommand(void) {}

void	KickCommand::execute(void) const {
	if (this->_args.size() < 4)
		throw ERR_NEEDMOREPARAMS(this->_name);

	Channel	*channel = this->_server->findChannelByName(this->_args[1]);

	if (!channel)
		throw ERR_NOSUCHCHANNEL(this->_args[1]);
	if (!channel->isOperator(this->_user))
		throw ERR_CHANOPRIVSNEEDED(channel->getName());

	std::string	target = this->_args[2];
	User	*targetUser = this->_server->findUserByName(target);

	if (!targetUser)
		throw ERR_NOSUCHNICK(target);
	if (!channel->isInChannel(targetUser))
		throw ERR_USERNOTINCHANNEL(channel->getName(), target);

	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	std::string response = userId + " KICK " + channel->getName() + " " + targetUser->getNickname() + " :" + this->_args[3] + "\r\n";

	channel->broadcast(response);
	channel->removeUser(targetUser);
}
