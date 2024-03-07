/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:20:06 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/05 11:01:16 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PingCommand.hpp"

PingCommand::PingCommand(void) : ACommand("PING") {}

PingCommand::~PingCommand(void) {}

void	PingCommand::execute(void) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	
	if (this->_args.size() < 1)
		throw ERR_NEEDMOREPARAMS(userId, this->_user->getNickname(), this->_name);

	std::string	response = userId + " PONG :" + this->_user->getNickname() + "\r\n";

	this->_user->addSendBuffer(response);
}
