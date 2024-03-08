/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:02:26 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/08 10:47:32 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Utils.hpp"

int	Utils::stoi(std::string &s) {
	int i;

	std::istringstream(s) >> i;
	return (i);
}

std::string	Utils::getCompletionJson(const std::string& nickname, const std::string& channel, const std::string& message) {
	std::ostringstream jsonPayload;
	jsonPayload << "{\"channel_id\": \"" << channel << "\", \"message\": {\"content\": \"" << message << "\", \"author\": \"" << nickname << "\"}}";
	return jsonPayload.str();
}
