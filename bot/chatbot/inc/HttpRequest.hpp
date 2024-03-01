#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <string>
# include "SocketHandler.hpp"
# include "JsonBuilder.hpp"

class HttpRequest {

    private:
        SocketHandler   _socketHandler;
        JsonBuilder     _jsonBuilder;
        std::string     _request;

    public:
        HttpRequest(int port);
        std::string getAPIResponse(const std::string& nickname, const std::string& channel, const std::string& message);
        void sendRequest();
        std::string receiveResponse();
};

#endif
