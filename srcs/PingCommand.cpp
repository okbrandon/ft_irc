/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:20:06 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/23 11:59:09 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PingCommand.hpp"

PingCommand::PingCommand(void) : ACommand("PING") {}

PingCommand::~PingCommand(void) {}

void	PingCommand::execute(void) const {
	if (this->_args.size() < 1)
		throw ERR_NEEDMOREPARAMS(this->_name);

	this->_user->addSendBuffer("PONG :" + this->_user->getNickname() + "\r\n");
}
