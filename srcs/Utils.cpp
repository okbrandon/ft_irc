/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:16:32 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/04 10:07:24 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Utils.hpp"

int	Utils::stoi(std::string &s) {
	int i;

	std::istringstream(s) >> i;
	return (i);
}

std::string	Utils::fixWidth(std::string str, int truncateAt) {
	if (static_cast<int>(str.length()) > truncateAt) {
		str = str.substr(0, 9);
		str.push_back('.');
	}
	return (str);
}

std::string	Utils::removeEndOccurrence(std::string str, std::string find) {
	while (true) {
		size_t pos = str.size() - find.size();

		if (pos < 0 || str.substr(pos) != find)
			break;
		str.erase(pos, find.size());
	}   
	return (str);
}

std::deque<std::string>	Utils::split(std::string message, std::string delimiters) {
	std::deque<std::string>		args;
	std::string					token;
	size_t						pos = 0;

	while ((pos = message.find_first_of(delimiters)) != std::string::npos) {
		token = message.substr(0, pos);

		if (!token.empty())
			args.push_back(token);
		message.erase(0, pos + 1);
	}
	if (!message.empty())
		args.push_back(message);
	return (args);
}
