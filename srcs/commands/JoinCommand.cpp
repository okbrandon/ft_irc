/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:15:06 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/13 11:37:25 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/commands/JoinCommand.hpp"

JoinCommand::JoinCommand(void) : ACommand("JOIN") {}

JoinCommand::~JoinCommand(void) {}

std::string	JoinCommand::_getStringifiedUsers(Channel *channel) const {
	std::vector<User*>	vect = channel->getUsers();
	std::string	users = "";

	for (std::vector<User*>::iterator it = vect.begin(); it != vect.end(); it++) {
		User	*user = *it;

		if (!users.empty())
			users.append(" ");
		if (channel->isOperator(user))
			users.append("@");
		users.append(user->getNickname());
	}
	return (users);
}

std::string	JoinCommand::_getChannelMode(Channel *channel) const {
	std::vector<char>	vect = channel->getModes();
	std::string	mode = "";

	for (std::vector<char>::iterator it = vect.begin(); it != vect.end(); it++) {
		std::string	str(1, *it);
		mode.append(str);
	}
	return (mode);
}

void	JoinCommand::_leaveAllChannels(void) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	std::map<std::string, Channel*>	channels = this->_server->getChannelsWhereUser(this->_user);

	if (channels.empty())
		return ;

	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
		Channel		*channel = it->second;
		std::string response = userId + " PART " + channel->getName() + " :Left all channels" + "\r\n";

		channel->broadcast(response);
	}
}

void	JoinCommand::execute(void) const {
	std::string				userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());

	if (this->_args.size() < 2 || this->_args.size() > 4)
		throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);
	if (!this->_args.at(1).compare("0")) {
		this->_leaveAllChannels();
		return ;
	}

	std::deque<std::string>	channels = Utils::split(this->_args[1], ",");
	std::deque<std::string>	keys;

	if (this->_args.size() == 3)
		keys = Utils::split(this->_args[2], ",");
	else
		keys = std::deque<std::string>();

	std::deque<std::string>::iterator	keysIt = keys.begin();
	for (std::deque<std::string>::iterator channelsIt = channels.begin(); channelsIt != channels.end(); channelsIt++) {
		std::string	channelName = *channelsIt;

		if (channelName.at(0) != '#') {
			this->_user->addSendBuffer(ERR_BADCHANMASK(userId, this->_user->getNickname(), channelName));
			continue ;
		}

		Channel	*channel = this->_server->findChannelByName(channelName);
		std::string key = keysIt != keys.end() ? *keysIt++ : "";
		
		if (!channel) { // channel is inexistant, creating one
			Channel *newChannel = new Channel(channelName);

			newChannel->setOwner(this->_user);
			newChannel->addOperator(this->_user);
			if (!key.empty()) {
				newChannel->addMode('k');
				newChannel->setKey(key);
			}
			newChannel->addUser(this->_user);
			this->_server->addChannel(newChannel);
			channel = newChannel;
		}
		else { // channel is existing, continuing process
			if (channel->hasMode('k') && channel->getKey() != key) { // channel is key protected
				this->_user->addSendBuffer(ERR_BADCHANNELKEY(userId, this->_user->getNickname(), channelName));
				continue ;
			}
			if (channel->hasMode('l')) { // channel has user limit
				if (channel->getUsers().size() >= channel->getLimit()) {
					this->_user->addSendBuffer(ERR_CHANNELISFULL(userId, this->_user->getNickname(), channelName));
					continue ;
				}
			}
			if (channel->hasMode('i') && !channel->isInvited(this->_user)) { // channel is invite-only
				this->_user->addSendBuffer(ERR_INVITEONLYCHAN(userId, this->_user->getNickname(), channelName));
				continue ;
			}
			channel->addUser(this->_user);
		}
		std::string	channelMode = this->_getChannelMode(channel);
		std::string	userList = this->_getStringifiedUsers(channel);

		channel->broadcast(userId + " JOIN :" + channelName + "\r\n");
		if (!channel->getTopic().empty())
			this->_user->addSendBuffer(RPL_TOPIC(userId, this->_user->getNickname(), channelName, channel->getTopic()));
		this->_user->addSendBuffer(RPL_NAMREPLY(userId, this->_user->getNickname(), "=", channelName, userList));
		this->_user->addSendBuffer(RPL_ENDOFNAMES(userId, this->_user->getNickname(), channelName));
		this->_user->addSendBuffer(RPL_CHANNELMODEIS(userId, this->_user->getNickname(), channelName, channel->getModeString()));
		if (channel->isInvited(this->_user))
			channel->removeInvitation(this->_user);
	}
}
