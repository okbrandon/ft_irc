/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCBot.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:28 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/07 12:10:17 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCBot.hpp"

const int MAX_BUFFER_SIZE = 1024;

IRCBot::IRCBot(int port) : _nickname("Booty"), _realname("booty"), _socketHandler(port), _httpRequest(443) { }
    
void IRCBot::connect(const char* server, const char* password, const char* channel) {
    _socketHandler.createSocket();
    _socketHandler.connectSocket(server);

    if (password != NULL && strlen(password) > 0) {
        std::string passMsg = "PASS ";
        passMsg += password;
        passMsg += "\r\n";
        sendMsg(passMsg.c_str());
    }

    std::string nickMsg = "NICK " + _nickname + "\r\n";
    std::string userMsg = "USER " + _username + " 0 * :" + _realname + "\r\n";
    std::string joinMsg = "JOIN " + std::string(channel) + "\r\n";
    sendMsg(nickMsg.c_str());
    sendMsg(userMsg.c_str());
    sendMsg(joinMsg.c_str());

    receiveMsg(); 
}

void IRCBot::sendMsg(const char* message) {
    sendMessage(_socketHandler.getSocket(), message, strlen(message), 0);
}

void IRCBot::receiveMsg() {
    char buffer[MAX_BUFFER_SIZE];
    while (true) {
        ssize_t bytesRead = recv(_socketHandler.getSocket(), buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << "Connection closed or error occurred.\n";
            break;
        }

        buffer[bytesRead] = '\0';
        handleMessage(buffer);
    }
}

void IRCBot::sendMessage(int socket, const char* message, size_t length, int flags) {
    ssize_t bytesSent = send(socket, message, length, flags);
    if (bytesSent == -1) {
        perror("Error sending message");
    }
}

void IRCBot::handleMessage(const std::string& raw) {
    if (raw.find("PING") != std::string::npos) {
        std::string pongMsg = "PONG\r\n";
        std::cout << "Sending PONG" << std::endl;
        sendMessage(_socketHandler.getSocket(), pongMsg.c_str(), pongMsg.length(), 0);
        return;
    }

    if (raw.find("PRIVMSG") != std::string::npos) {
        size_t pos1 = raw.find(':') + 1, pos2 = raw.find('!', pos1);
        std::string nickname = raw.substr(pos1, pos2 - pos1);

        size_t channelPos1 = raw.find('#'), channelPos2 = raw.find(' ', channelPos1);
        std::string channel = raw.substr(channelPos1, channelPos2 - channelPos1);

        size_t messagePos = raw.find(':', channelPos2);
        std::string message = raw.substr(messagePos + 1);
    
        message.erase(message.find_last_not_of(" \n\r\t") + 1);

        std::string completion = _httpRequest.getAPIResponse(nickname, channel, message);
        
        std::string response = "PRIVMSG " + channel + " :" + completion + "\r\n";
        sendMessage(_socketHandler.getSocket(), response.c_str(), response.length(), 0);
    }
}