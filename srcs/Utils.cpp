/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:16:32 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/01/29 20:08:49 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Utils.hpp"

int	Utils::stoi(std::string &s) {
	int i;

	std::istringstream(s) >> i;
	return (i);
}

std::vector<std::string>	Utils::getSplittedMessage(std::string &message) {
	std::vector<std::string>	commands;
	std::string	delimiter = "\n";
	std::string::size_type to;

	for (to = message.find(delimiter); to != std::string::npos; to = message.find(delimiter)) {
		commands.push_back(message.substr(0, to));
		message.erase(0, to + delimiter.size());
	}
	return (commands);
}
