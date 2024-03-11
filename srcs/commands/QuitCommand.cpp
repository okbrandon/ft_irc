/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:30:10 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 17:57:06 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/commands/QuitCommand.hpp"

QuitCommand::QuitCommand(void) : ACommand("QUIT") {}

QuitCommand::~QuitCommand(void) {}

void	QuitCommand::execute(void) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	Channel	*channel = this->_server->findChannelByUser(this->_user);

	if (!channel)
		return ;
	
	std::string	reason;
	for (size_t i = 1; i < this->_args.size(); i++) {
		if (!reason.empty())
			reason.append(" ");
		reason.append(this->_args[i]);
	}

	std::string	response = userId + " QUIT " + (reason.empty() ? ":Client Quit" : reason) + "\r\n";
	channel->broadcast(response);
}
