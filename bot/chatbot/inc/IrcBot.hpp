#ifndef IRCBOT_H
# define IRCBOT_H

# include <string>
# include "SocketHandler.hpp"
# include "HttpRequest.hpp"

class IrcBot {

    private:
        std::string     _nickname;
        std::string     _username;
        std::string     _realname;
    
        SocketHandler   _socketHandler;
        HttpRequest     _httpRequest;
    
    public:
        IrcBot(int port);

        void connect(const char* server, const char* password, const char* channel);
        void sendMsg(const char* message);
        void receiveMsg(void);
        void sendMessage(int socket, const char* message, size_t length, int flags);
        void handleMessage(const std::string& raw);
};

#endif
