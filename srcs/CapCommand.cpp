/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CapCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:42:05 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/12 17:08:33 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/CapCommand.hpp"

CapCommand::CapCommand(void) : ACommand("CAP") {}

CapCommand::~CapCommand(void) {}

void	CapCommand::execute(void) const {
	if (this->_args.size() >= 2 && !this->_args.at(1).compare("LS")) {
		this->_user->sendDirectMessage(": CAP * LS :\r\n");
	}
	else if (this->_args.size() >= 3 && !this->_args.at(1).compare("REQ")) {
		std::string	requestedFeatures = this->_args.at(2).substr(1);

		for (size_t i = 3; i < this->_args.size(); i++)
			requestedFeatures.append(" ").append(this->_args.at(i));
		
		this->_user->sendDirectMessage(": CAP * NAK :" + requestedFeatures + "\r\n");
	}
}
