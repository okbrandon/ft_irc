/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:47:31 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/08 10:26:58 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "IRCDepends.hpp"

/* Soft-depending */
class SocketHandler;

class HttpRequest {

    private:
        SocketHandler   *_socketHandler;
        std::string     _request;

        HttpRequest(void);
        HttpRequest(const HttpRequest &origin);

        void            _sendRequest();
        std::string     _receiveResponse();

        HttpRequest &operator=(const HttpRequest &origin);

    public:
        HttpRequest(int port);
        ~HttpRequest(void);

        std::string     getAPIResponse(const std::string& nickname, const std::string& channel, const std::string& message);
};

#endif
