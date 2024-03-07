/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:33 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/07 11:51:34 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCBot.hpp"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <server> <port> <password> <channel>\n";
        return EXIT_FAILURE;
    }

    const char* server = argv[1];
    int port = std::atoi(argv[2]);
    const char* password = argv[3];
    const char* channel = argv[4];

    IRCBot bot(port);
    bot.connect(server, password, channel);

    return EXIT_SUCCESS;
}
