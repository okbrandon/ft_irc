/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:06:26 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 16:35:11 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PartCommand.hpp"

PartCommand::PartCommand(void) : ACommand("PART") {}

PartCommand::~PartCommand(void) {}

void	PartCommand::execute(void) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());

	if (this->_args.size() < 2)
		throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);

	std::deque<std::string>	channels = Utils::split(this->_args[1], ",");

	for (std::deque<std::string>::iterator channelsIt = channels.begin(); channelsIt != channels.end(); channelsIt++) {
		std::string	channelName = *channelsIt;

		if (channelName.at(0) != '#') {
			this->_user->addSendBuffer(ERR_BADCHANMASK(userId, this->_user->getNickname(), channelName));
			continue ;
		}

		Channel	*channel = this->_server->findChannelByName(channelName);

		if (!channel) {
			this->_user->addSendBuffer(ERR_NOSUCHCHANNEL(userId, this->_user->getNickname(), channelName));
			continue ;
		}

		if (!channel->isInChannel(this->_user)) {
			this->_user->addSendBuffer(ERR_NOTONCHANNEL(userId, this->_user->getNickname(), channelName));
			continue ;
		}

		std::string	reason;
		for (size_t i = 2; i < this->_args.size(); i++) {
			if (!reason.empty())
				reason.append(" ");
			reason.append(this->_args[i]);
		}
		
		std::string response = userId + " PART " + channel->getName() + " " + reason + "\r\n";
		
		channel->broadcast(response);
		channel->removeUser(this->_user);
	}
}
