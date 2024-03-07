/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:48:08 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/07 11:48:09 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETHANDLER_H
# define SOCKETHANDLER_H

# include "IRCDepends.hpp"

class SocketHandler {

    private:
        int         _socket;
        sockaddr_in _address;
        int         _port; 
    
    public:
        SocketHandler(int port);
        ~SocketHandler(void);

        void    createSocket(void);
        void    connectSocket(std::string addr);
        void    closeSocket(void);
        int     getSocket(void) const;
};

#endif
