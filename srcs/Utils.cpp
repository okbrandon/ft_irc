/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:16:32 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/02 09:46:05 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Utils.hpp"

int	Utils::stoi(std::string &s) {
	int i;

	std::istringstream(s) >> i;
	return (i);
}

std::vector<std::string>	Utils::getSplittedMessage(std::string &message) {
	std::vector<std::string>	commandArgs;
	std::string					delimiters = " \n";
	size_t						pos = 0;

	while ((pos = message.find_first_of(delimiters)) != std::string::npos) {
		commandArgs.push_back(message.substr(0, pos));
		message.erase(0, pos + 1);
	}
	if (!message.empty())
		commandArgs.push_back(message);
	return (commandArgs);
}
