/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCLogger.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:21:16 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/29 10:14:57 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCLogger.hpp"

IRCLogger::IRCLogger(void) {}

IRCLogger::IRCLogger(const IRCLogger &origin) {
	*this = origin;
}

IRCLogger::~IRCLogger(void) {}

void	IRCLogger::queue(std::string message) {
	this->_queuedMessages.push_back(message);
}

void	IRCLogger::printQueue(void) {
	if (LOGS) {	
		for (std::deque<std::string>::iterator it = this->_queuedMessages.begin(); it != this->_queuedMessages.end(); it++) {
			std::string	message = *it;
			std::cout << message;
		}
	}
	this->_queuedMessages.clear();
}

void	IRCLogger::destroy(void) {
	IRCLogger	*instance = getInstance();

	delete instance;
}

IRCLogger	&IRCLogger::operator=(const IRCLogger &origin) {
	this->_queuedMessages = origin._queuedMessages;
	return (*this);
}

IRCLogger	*IRCLogger::getInstance(void) {
	static IRCLogger	*instance = new IRCLogger();

	return (instance);
}
