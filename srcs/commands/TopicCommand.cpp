/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:30 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/11 17:57:07 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/commands/TopicCommand.hpp"

TopicCommand::TopicCommand(void) : ACommand("TOPIC") {}

TopicCommand::~TopicCommand(void) {}

// NOTE: Irssi seems to expect TOPIC msgs to ommit the channel argument.
void	TopicCommand::execute(void) const {
	std::string userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());

	if (this->_args.size() < 2)
		throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);

	Channel		*channel = this->_server->findChannelByName(this->_args[1]);

	if (!channel)
		throw ERR_NOSUCHCHANNEL(userId, this->_user->getNickname(), this->_args[1]);

	if (this->_args.size() == 2) {
		if (channel->getTopic().empty())
			this->_user->addSendBuffer(RPL_NOTOPIC(userId, this->_user->getNickname(), channel->getName()));
		else
			this->_user->addSendBuffer(RPL_TOPIC(userId, this->_user->getNickname(), channel->getName(), channel->getTopic()));
		return ;
	}

	if (!channel->isInChannel(this->_user))
		throw ERR_NOTONCHANNEL(userId, this->_user->getNickname(), channel->getName());
	if (!channel->hasMode('t') && !channel->isOperator(this->_user))
		throw ERR_CHANOPRIVSNEEDED(userId, this->_user->getNickname(), channel->getName());

	std::string	topic;
	for (size_t i = 2; i < this->_args.size(); i++) {
		if (!topic.empty())
			topic.append(" ");
		topic.append(this->_args[i]);
	}
	
	std::string response = userId + " TOPIC " + channel->getName() + " " + topic + "\r\n";

	channel->setTopic(topic.at(0) == ':' ? topic.erase(0, 1) : topic);
	channel->broadcast(response);
}
