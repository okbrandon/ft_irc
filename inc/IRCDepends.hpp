/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCDepends.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:53:58 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/01/19 17:18:52 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCDEPENDS_HPP
# define IRCDEPENDS_HPP

# include <iostream>
# include <sstream>
# include <iomanip>
# include <cstring>
# include <map>
# include <vector>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <poll.h>
# include <unistd.h>

# include "Utils.hpp"
# include "User.hpp"
# include "Server.hpp"

# define MAX_CONNECTIONS    10

#endif