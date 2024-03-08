/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:24 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/08 10:23:43 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/HttpRequest.hpp"

HttpRequest::HttpRequest(void) {}

HttpRequest::HttpRequest(int port) {
    this->_socketHandler = new SocketHandler(port);
}

HttpRequest::HttpRequest(const HttpRequest &origin) {
    *this = origin;
}

HttpRequest::~HttpRequest(void) {
    delete this->_socketHandler;
}

void HttpRequest::_sendRequest() {
    send(_socketHandler->getSocket(), _request.c_str(), _request.length(), 0);
}

std::string HttpRequest::_receiveResponse() {
    char buffer[MAX_BUFFER_SIZE];
    std::string response;

    while (true) {
        ssize_t bytesRead = recv(_socketHandler->getSocket(), buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << "Error receiving response from API server.\n";
            break;
        }

        buffer[bytesRead] = '\0';
        response += buffer;

        // Assuming the response ends with '\r\n\r\n' to indicate the end of the HTTP header
        if (strstr(response.c_str(), "\r\n\r\n") != NULL) {
            break;
        }
    }

    size_t jsonStart = response.find("\r\n\r\n");
    if (jsonStart != std::string::npos) {
        jsonStart += 4; // Move past the '\r\n\r\n'
        std::string jsonResponse = response.substr(jsonStart);
        size_t responseStart = jsonResponse.find("\"response\":");
        if (responseStart != std::string::npos) {
            responseStart += 12; // Move past the '\"response\":'
            size_t responseEnd = jsonResponse.find("\"", responseStart);
            if (responseEnd != std::string::npos) {
                std::string responseValue = jsonResponse.substr(responseStart, responseEnd - responseStart);
                return responseValue;
            }
        }
    }
    return "Hello! I'm currently unavailable. Please call back later.";
}

std::string HttpRequest::getAPIResponse(const std::string& nickname, const std::string& channel, const std::string& message) {
    _socketHandler->createSocket();
    _socketHandler->connectSocket("23.169.88.99");

    std::string jsonPayload = Utils::getCompletionJson(nickname, channel, message);

    _request = "POST /api/v1/chat HTTP/1.1\r\n"
               "Host: 23.169.88.99\r\n"
               "Content-Type: application/json\r\n"
               "Content-Length: " + Utils::toString(jsonPayload.length()) + "\r\n"
               "User-Agent: Booty\r\n" +
               "\r\n" +
               jsonPayload;

    _sendRequest();
    std::string response = _receiveResponse();

    _socketHandler->closeSocket();

    return response;
}

HttpRequest &HttpRequest::operator=(const HttpRequest &origin) {
    this->_request = origin._request;
    this->_socketHandler = origin._socketHandler;
    return (*this);
}
