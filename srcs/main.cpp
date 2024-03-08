/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:52:31 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/08 10:51:55 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCDepends.hpp"

// Global attribute that handles the server status
bool	g_server_running = false;

bool	_isPortValid(char *port) {
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

void	_handleSignal(int signal) {
	g_server_running = false;
	std::cout << Utils::toString(SERVER_INFO) << "bai bai :c" << std::endl;
	(void) signal;
}

int	main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "Invalid args.\n./ircserv <port> <password>" << std::endl;
		return (1);
	}
	if (!_isPortValid(argv[1])) {
		std::cerr << "Invalid port." << std::endl;
		return (1);
	}
	try {
		std::string	password = Utils::toString(argv[2]);
		std::string	portAsString = Utils::toString(argv[1]);
		int port = Utils::stoi(portAsString);

		std::cout << BGRN "Should be fine." CRESET << std::endl;
		// Handling signals
		signal(SIGINT, _handleSignal);
		signal(SIGQUIT, _handleSignal);
		// Starting server
		Server	ircServer("127.0.0.1", port, password);
		ircServer.run();
	} catch (std::exception &exception) {
		std::cerr << Utils::toString(SERVER_KO) << "Exception caught!" << std::endl;
		std::cerr << exception.what() << std::endl;
	}
	IRCLogger::getInstance()->destroy();
	return (0);
}
