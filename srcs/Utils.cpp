/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:16:32 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/09 15:50:07 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Utils.hpp"

int	Utils::stoi(std::string &s) {
	int i;

	std::istringstream(s) >> i;
	return (i);
}

std::deque<std::string>	Utils::splitArguments(std::string &message) {
	std::deque<std::string>		commandArgs;
	std::string					delimiters = " \t\r";
	std::string					token;
	size_t						pos = 0;

	while ((pos = message.find_first_of(delimiters)) != std::string::npos) {
		token = message.substr(0, pos);

		if (!token.empty())
			commandArgs.push_back(token);
		message.erase(0, pos + 1);
	}
	return (commandArgs);
}

std::deque<std::string>	Utils::splitCommands(std::string &message) {
	std::deque<std::string>		commands;
	std::string					delimiters = "\n\v";
	std::string					token;
	size_t						pos = 0;

	while ((pos = message.find_first_of(delimiters)) != std::string::npos) {
		token = message.substr(0, pos);

		if (!token.empty())
			commands.push_back(token);
		message.erase(0, pos + 1);
	}
	return (commands);
}
