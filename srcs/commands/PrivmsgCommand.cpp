/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:14:33 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/14 10:06:37 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/commands/PrivmsgCommand.hpp"

PrivmsgCommand::PrivmsgCommand(void) : ACommand("PRIVMSG") {
	this->addAlias("NOTICE");
}

PrivmsgCommand::~PrivmsgCommand(void) {}

bool	PrivmsgCommand::_sendChannelMessage(std::string channelName, std::string message) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	Channel	*channel = this->_server->findChannelByName(channelName);

	if (!channel) {
		this->_user->addSendBuffer(ERR_NOSUCHNICK(userId, this->_user->getNickname(), channelName));
		return (false);
	}
	if (!channel->isInChannel(this->_user)) {
		this->_user->addSendBuffer(ERR_NOTONCHANNEL(userId, this->_user->getNickname(), channelName));
		return (false);
	}

	std::string response = userId + " " + this->getCalledCommand() + " " + channelName + " " + message + "\r\n";

	channel->excludeBroadcast(response, this->_user);
	return (true);
}

bool	PrivmsgCommand::_sendUserMessage(std::string nickName, std::string message) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	User	*target = this->_server->findUserByName(nickName);

	if (!target) {
		this->_user->addSendBuffer(ERR_NOSUCHNICK(userId, this->_user->getNickname(), nickName));
		return (false);
	}

	std::string response = userId + " " + this->getCalledCommand() + " " + target->getNickname() + " " + message + "\r\n";

	target->addSendBuffer(response);
	return (true);
}

std::string	PrivmsgCommand::_getMessage(void) const {
	std::string	message;

	for (size_t i = 2; i < this->_args.size(); i++) {
		if (!message.empty())
			message.append(" ");
		message.append(this->_args[i]);
	}
	return (message);
}

void	PrivmsgCommand::execute(void) const {
	std::string				userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	std::deque<std::string>	recipients;
	std::string				message;

	if (this->_args.size() < 3) {
		this->_user->addSendBuffer(ERR_NORECIPIENT(userId, this->_user->getNickname(), this->_name));
		return ;
	}
	
	recipients = Utils::split(this->_args[1], ",");
	if (recipients.size() == 0) {
		this->_user->addSendBuffer(ERR_NORECIPIENT(userId, this->_user->getNickname(), this->_name));
		return ;
	}

	message = this->_getMessage();
	for (std::deque<std::string>::iterator it = recipients.begin(); it != recipients.end(); it++) {
		std::string	recipientName = *it;

		if (recipientName.at(0) == '#') {
			if (!this->_sendChannelMessage(recipientName, message))
				return ;
			continue ;
		}
		this->_sendUserMessage(recipientName, message);
	}
}
