/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:33 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/08 10:50:30 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCBot.hpp"

bool    _isPortValid(char *port) {
    std::string	portAsString = Utils::toString(port);

    // Check if it is only integers
    for (size_t i = 0; i < portAsString.size(); i++) {
        if (!std::isdigit(portAsString.at(i)))
            return (false);
    }
    // Extracting port
    int num = Utils::stoi(portAsString);
    return (num > 0 && num < 65535);
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		std::cerr << "Invalid args.\n./ircbot <host> <password> <port> <channel>" << std::endl;
		return (1);
	}
	if (!_isPortValid(argv[2])) {
		std::cerr << "Invalid port." << std::endl;
		return (1);
	}

    const char* server = argv[1];
    const char* password = argv[3];
    const char* channel = argv[4];
    std::string	portAsString = Utils::toString(argv[2]);
    int port = Utils::stoi(portAsString);

    IRCBot bot(port);
    bot.connect(server, password, channel);

    return EXIT_SUCCESS;
}
