/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:47:31 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/07 12:09:35 by bsoubaig         ###   ########.fr       */
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

    public:
        HttpRequest(int port);
        ~HttpRequest(void);

        std::string getAPIResponse(const std::string& nickname, const std::string& channel, const std::string& message);
        void sendRequest();
        std::string receiveResponse();
};

#endif
