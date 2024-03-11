/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:18 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/11 17:56:50 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/commands/ModeCommand.hpp"

ModeCommand::ModeCommand(void) : ACommand("MODE") {}

ModeCommand::~ModeCommand(void) {}

bool	ModeCommand::_addMode(Channel *channel) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	std::string	modes = this->_args[2];

	if (modes.at(0) == '+')
		modes.erase(0, 1);
	// set invite-only
	if (modes.at(0) == 'i') {
		if (channel->hasMode('i'))
			return (false);
		channel->addMode('i');
	}
	// remove topic restrictions
	if (modes.at(0) == 't') {
		if (channel->hasMode('t'))
			return (false);
		channel->addMode('t');
	}
	// add key
	if (modes.at(0) == 'k') {
		if (this->_args.size() < 4) {
			throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);
			return (false);
		}
		if (channel->hasMode('k'))
			return (false);
		channel->addMode('k');
		channel->setKey(this->_args[3]);
	}
	// add operator
	if (modes.at(0) == 'o') {
		if (this->_args.size() < 4) {
			throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);
			return (false);
		}
		
		User	*target = this->_server->findUserByName(this->_args[3]);

		if (!target) {
			throw ERR_NOSUCHNICK(userId, this->_user->getNickname(), this->_args[3]);
			return (false);
		}
		if (!channel->isInChannel(target)) {
			throw ERR_USERNOTINCHANNEL(userId, this->_user->getNickname(), channel->getName(), target->getNickname());
			return (false);
		}
		if (channel->isOperator(target))
			return (false);
		channel->addOperator(target);
	}
	// limit set
	if (modes.at(0) == 'l') {
		if (this->_args.size() < 4) {
			throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);
			return (false);
		}
		std::string	limitString = this->_args[3];
		int	limit = Utils::stoi(limitString);

		if (limit < 0)
			return (false);
		if (channel->hasMode('l'))
			return (false);
		channel->addMode('l');
		channel->setLimit(limit);
	}
	return (true);
}

bool	ModeCommand::_removeMode(Channel *channel) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	std::string	modes = this->_args[2];

	if (modes.at(0) != '-')
		return (false);
	modes.erase(0, 1);

	// remove invite-only
	if (modes.at(0) == 'i') {
		if (!channel->hasMode('i'))
			return (false);
		channel->removeMode('i');
	}
	// set topic restrictions 
	if (modes.at(0) == 't') {
		if (!channel->hasMode('t'))
			return (false);
		channel->removeMode('t');
	}
	// remove key
	if (modes.at(0) == 'k') {
		if (!channel->hasMode('k'))
			return (false);
		channel->removeMode('k');
		channel->setKey("");
	}
	// remove operator
	if (modes.at(0) == 'o') {
		if (this->_args.size() < 4) {
			throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);
			return (false);
		}
		
		User	*target = this->_server->findUserByName(this->_args[3]);

		if (!target) {
			throw ERR_NOSUCHNICK(userId, this->_user->getNickname(), this->_args[3]);
			return (false);
		}
		if (!channel->isOperator(target))
			return (false);
		channel->removeOperator(target);
	}
	// remove limit
	if (modes.at(0) == 'l') {
		if (!channel->hasMode('l')) {
			return (false);
		}
		channel->removeMode('l');
	}
	return (true);
}

void	ModeCommand::execute(void) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());

	if (this->_args.size() < 2)
		throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);

	Channel		*channel = this->_server->findChannelByName(this->_args[1]);

	if (!channel)
		throw ERR_NOSUCHCHANNEL(userId, this->_user->getNickname(), this->_args[1]);
	if (!channel->isInChannel(this->_user))
		throw ERR_NOTONCHANNEL(userId, this->_user->getNickname(), this->_args[1]);
	if (this->_args.size() == 2) {
		this->_user->addSendBuffer(RPL_CHANNELMODEIS(userId, this->_user->getNickname(), channel->getName(), channel->getModeString()));
		return ;
	}
	if (!channel->isOperator(this->_user))
		throw ERR_CHANOPRIVSNEEDED(userId, this->_user->getNickname(), channel->getName());
	
	std::string	modes = this->_args[2];
	std::string	availableModes = "itkol+-";
	bool		updatedModes = false;

	if (availableModes.find(modes[0]) == std::string::npos)
		throw ERR_UNKNOWNMODE(userId, this->_user->getNickname(), Utils::toString(modes[0]));

	if (modes.at(0) == '-' && modes.size() > 1)
		updatedModes = this->_removeMode(channel);
	else if (modes.size() > 1)
		updatedModes = this->_addMode(channel);
	if (updatedModes)
		this->_user->addSendBuffer(RPL_CHANNELMODEIS(userId, this->_user->getNickname(), channel->getName(), channel->getModeString()));
}
