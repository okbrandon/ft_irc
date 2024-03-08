/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCDepends.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:45:51 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/08 10:27:01 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCDEPENDS_HPP
# define IRCDEPENDS_HPP

# include <cstring>
# include <string>
# include <sstream>
# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <unistd.h>

# include "Utils.hpp"
# include "SocketHandler.hpp"
# include "HttpRequest.hpp"

const int MAX_BUFFER_SIZE = 1024;

#endif
