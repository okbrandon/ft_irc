#include "../inc/HttpRequest.hpp"
#include <string>
#include <iostream>
#include <cstring>

const int MAX_BUFFER_SIZE = 1024;

HttpRequest::HttpRequest(int port) : _socketHandler(port) { }

std::string HttpRequest::getAPIResponse(const std::string& nickname, const std::string& channel, const std::string& message) {
    _socketHandler.createSocket();
    _socketHandler.connectSocket("https://api.evan.sh/api/v1/chat");

    std::string jsonPayload = _jsonBuilder.getCompletionJson(nickname, channel, message);

    _request = "POST /api/v1/chat HTTP/1.1\r\n"
               "Host: api.evan.sh\r\n"
               "Content-Type: application/json\r\n"
               "Content-Length: " + std::to_string(jsonPayload.length()) + "\r\n"
               "User-Agent: Booty\r\n" +
               "\r\n" +
               jsonPayload;

    sendRequest();
    std::string response = receiveResponse();

    _socketHandler.closeSocket();

    return response;
}

void HttpRequest::sendRequest() {
    send(_socketHandler.getSocket(), _request.c_str(), _request.length(), 0);
}

std::string HttpRequest::receiveResponse() {
    char buffer[MAX_BUFFER_SIZE];
    std::string response;

    while (true) {
        ssize_t bytesRead = recv(_socketHandler.getSocket(), buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << "Error receiving response from API server.\n";
            break;
        }

        buffer[bytesRead] = '\0';
        response += buffer;

        // Assuming the response ends with '\r\n\r\n' to indicate the end of the HTTP header
        if (strstr(response.c_str(), "\r\n\r\n") != nullptr) {
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
