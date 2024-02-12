/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:29:15 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/12 17:04:43 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Executor.hpp"
#include "../inc/PassCommand.hpp"
#include "../inc/NickCommand.hpp"
#include "../inc/UserCommand.hpp"
#include "../inc/PingCommand.hpp"
#include "../inc/CapCommand.hpp"

Executor::Executor(void) {}

Executor::Executor(Server *server) {
	this->_server = server;
	this->_registerCommands();
}

Executor::Executor(Executor const &origin) {
	*this = origin;
}

Executor::~Executor(void) {
	for (std::deque<ACommand*>::iterator it = this->_commands.begin(); it != this->_commands.end(); it++) {
		delete *it;
		this->_commands.erase(it);
	}
	this->_commands.clear();
}

void	Executor::_registerCommands(void) {
	this->_commands.push_back(new PassCommand());
	this->_commands.push_back(new NickCommand());
	this->_commands.push_back(new UserCommand());
	this->_commands.push_back(new PingCommand());
	this->_commands.push_back(new CapCommand());
}

bool	Executor::_isRegisteredCommand(std::string input) {
	for (std::deque<ACommand*>::iterator it = this->_commands.begin(); it != this->_commands.end(); it++) {
		ACommand	*command = *it;

		if (!command->getName().compare(input))
			return (true);
	}
	return (false);
}

void	Executor::processCommand(User *user, std::deque<std::string> commandArgs) {
	std::string	commandName;

	if (commandArgs.empty() || !this->_isRegisteredCommand(commandArgs[0]))
		return ;
	commandName = commandArgs[0];
	for (std::deque<ACommand*>::iterator it = this->_commands.begin(); it != this->_commands.end(); it++) {
		ACommand	*command = *it;

		if (!command->getName().compare(commandName)) {
			command->setServer(this->_server);
			command->setUser(user);
			command->setArgs(commandArgs);
			try {
				command->execute();
			} catch (std::string message) {
				user->addSendBuffer(message);
			} catch (char const* message) {
				user->addSendBuffer(message);
			}
			break ;
		}
	}
}

Executor	&Executor::operator=(Executor const &origin) {
	this->_server = origin._server;
	this->_commands = origin._commands;
	return (*this);
}
