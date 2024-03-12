/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:30:10 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/12 11:46:10 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/commands/QuitCommand.hpp"

QuitCommand::QuitCommand(void) : ACommand("QUIT") {}

QuitCommand::~QuitCommand(void) {}

void	QuitCommand::execute(void) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	std::map<std::string, Channel*>	channels = this->_server->getChannelsWhereUser(this->_user);

	if (channels.empty())
		return ;
	
	std::string	reason;
	for (size_t i = 1; i < this->_args.size(); i++) {
		if (!reason.empty())
			reason.append(" ");
		reason.append(this->_args[i]);
	}

	std::string	response = userId + " QUIT " + (reason.empty() ? ":Client Quit" : reason) + "\r\n";

	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
		Channel	*channel = it->second;

		channel->broadcast(response);
	}
}
