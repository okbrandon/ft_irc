/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:24 by evmorvan          #+#    #+#             */
/*   Updated: 2024/02/26 09:57:24 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/KickCommand.hpp"

KickCommand::KickCommand(void) : ACommand("KICK") {}

KickCommand::~KickCommand(void) {}

void	KickCommand::execute(void) const {
	if (this->_args.size() < 4)
		throw ERR_NEEDMOREPARAMS(this->_name);
	
	std::cout << "1" << std::endl;

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
	if (!channel->isInChannel(targetUser)) // seems broken need investigate
		throw ERR_USERNOTINCHANNEL(channel->getName(), target);

	std::string kickMessage = ":" + this->_user->getNickname() + "!" + this->_user->getUsername() + "@localhost" + " KICK " + channel->getName() + " " + targetUser->getNickname() + " :" + this->_args[3] + "\r\n";
	channel->broadcast(kickMessage);
	channel->removeUser(targetUser);
}
