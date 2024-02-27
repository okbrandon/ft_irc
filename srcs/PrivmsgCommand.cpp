/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:14:33 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/27 16:17:57 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PrivmsgCommand.hpp"

PrivmsgCommand::PrivmsgCommand(void) : ACommand("PRIVMSG") {
	this->addAliase("NOTICE");
}

PrivmsgCommand::~PrivmsgCommand(void) {}

bool	PrivmsgCommand::_sendChannelMessage(std::string channelName, std::string message) const {
	Channel	*channel = this->_server->findChannelByName(channelName);

	if (!channel) {
		this->_user->addSendBuffer(ERR_NOSUCHNICK(channelName));
		return (false);
	}
	if (!channel->isInChannel(this->_user)) {
		this->_user->addSendBuffer(ERR_NOTONCHANNEL(channelName));
		return (false);
	}

	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	std::string response = userId + " " + this->getCalledCommand() + " " + channelName + " " + message + "\r\n";

	channel->excludeBroadcast(response, this->_user);
	return (true);
}

bool	PrivmsgCommand::_sendUserMessage(std::string nickName, std::string message) const {
	User	*target = this->_server->findUserByName(nickName);

	if (!target) {
		this->_user->addSendBuffer(ERR_NOSUCHNICK(nickName));
		return (false);
	}

	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
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
	std::deque<std::string>	recipients;
	std::string				message;

	if (this->_args.size() < 3) {
		this->_user->addSendBuffer(ERR_NORECIPIENT(this->_name));
		return ;
	}
	
	recipients = Utils::split(this->_args[1], ",");
	if (recipients.size() == 0) {
		this->_user->addSendBuffer(ERR_NORECIPIENT(this->_name));
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
