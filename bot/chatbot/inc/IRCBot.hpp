/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCBot.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:47:50 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/08 10:23:52 by bsoubaig         ###   ########.fr       */
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
        HttpRequest     *_httpRequest;
        SocketHandler   *_socketHandler;

        IRCBot(void);
        IRCBot(const IRCBot &origin);

        IRCBot  &operator=(const IRCBot &origin);

    public:
        IRCBot(int port);
        ~IRCBot(void);

        void connect(const char* server, const char* password, const char* channel);
        void sendMsg(const char* message);
        void receiveMsg(void);
        void sendMessage(int socket, const char* message, size_t length, int flags);
        void handleMessage(const std::string& raw);

};

#endif
