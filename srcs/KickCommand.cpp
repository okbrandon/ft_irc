/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:24 by evmorvan          #+#    #+#             */
/*   Updated: 2024/02/27 11:17:41 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/KickCommand.hpp"

KickCommand::KickCommand(void) : ACommand("KICK") {}

KickCommand::~KickCommand(void) {}

void	KickCommand::execute(void) const {
	if (this->_args.size() < 4)
		throw ERR_NEEDMOREPARAMS(this->_name);

	Channel	*channel = this->_server->findChannelByName(this->_args[1]);
	User	*user = this->_server->findUserByFd(this->_user->getSocket());

	if (!channel)
		throw ERR_NOSUCHCHANNEL(this->_args[1]);
	if (!user)
		throw ERR_USERNOTINCHANNEL(this->_args[1], this->_user->getNickname());
	if (!channel->isOperator(user))
		throw ERR_CHANOPRIVSNEEDED(channel->getName());

	std::string	target = this->_args[2];
	User	*targetUser = this->_server->findUserByName(target);

	if (!targetUser)
		throw ERR_NOSUCHNICK(target);
	if (!channel->isInChannel(targetUser)) // seems broken need investigate; (not broken, message is being sent into main buffer -brandon)
		throw ERR_USERNOTINCHANNEL(channel->getName(), target);

	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	std::string response = userId + " KICK " + channel->getName() + " " + targetUser->getNickname() + " :" + this->_args[3] + "\r\n";

	channel->broadcast(response);
	channel->removeUser(targetUser);
}
