#include "../inc/SocketHandler.hpp"
#include <iostream>

SocketHandler::SocketHandler(int port) : _socket(-1), _port(port) { }

SocketHandler::~SocketHandler() {
    closeSocket();
}

void SocketHandler::createSocket() {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
}

void SocketHandler::connectSocket(std::string addr) {
    _address.sin_family = AF_INET;
    _address.sin_port = htons(_port);  
    if (inet_pton(AF_INET, addr.c_str(), &(_address.sin_addr)) <= 0) {
        perror("Invalid address");
        close(_socket);
        exit(EXIT_FAILURE);
    }

    if (connect(_socket, reinterpret_cast<sockaddr*>(&_address), sizeof(_address)) == -1) {
        perror("Error connecting to server");
        close(_socket);
        exit(EXIT_FAILURE);
    }
}

void SocketHandler::closeSocket() {
    close(_socket);
}

int SocketHandler::getSocket() const {
    return _socket;
}
