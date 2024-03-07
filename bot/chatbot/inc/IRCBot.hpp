/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCBot.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:47:50 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/07 11:48:37 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCBOT_H
# define IRCBOT_H

# include "IRCDepends.hpp"

class IRCBot {

    private:
        std::string     _nickname;
        std::string     _username;
        std::string     _realname;
    
        SocketHandler   _socketHandler;
        HttpRequest     _httpRequest;
    
    public:
        IRCBot(int port);

        void connect(const char* server, const char* password, const char* channel);
        void sendMsg(const char* message);
        void receiveMsg(void);
        void sendMessage(int socket, const char* message, size_t length, int flags);
        void handleMessage(const std::string& raw);
};

#endif
