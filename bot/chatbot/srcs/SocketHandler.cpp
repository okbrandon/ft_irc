/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:36 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/08 10:22:19 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/SocketHandler.hpp"

SocketHandler::SocketHandler(void) {}

SocketHandler::SocketHandler(int port) : _socket(-1), _port(port) {}

SocketHandler::SocketHandler(const SocketHandler &origin) {
    *this = origin;
}

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

SocketHandler   &SocketHandler::operator=(const SocketHandler &origin) {
    this->_address = origin._address;
    this->_port = origin._port;
    this->_socket = origin._socket;
    return (*this);
}
