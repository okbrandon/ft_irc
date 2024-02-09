/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCDepends.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:53:58 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/09 10:21:47 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCDEPENDS_HPP
# define IRCDEPENDS_HPP

# include <iostream>
# include <sstream>
# include <iomanip>
# include <ctime>
# include <cstring>
# include <algorithm>
# include <map>
# include <vector>
# include <deque>
# include <list>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <poll.h>
# include <unistd.h>
# include <signal.h>
# include <stddef.h>

# include "IRCNumReplies.hpp"
# include "Utils.hpp"
# include "User.hpp"
# include "Server.hpp"
# include "ACommand.hpp"
# include "Executor.hpp"

# define BRED	"\033[1;31m"
# define BGRN	"\033[1;32m"
# define BYEL	"\033[1;33m"
# define BBLU	"\033[1;34m"
# define BMAG	"\033[1;35m"
# define BCYN	"\033[1;36m"
# define BWHT	"\033[1;37m"
# define CRESET	"\033[0m"

# define MAX_CONNECTIONS    10
# define SERVER_OK          BGRN "[Server] " CRESET
# define SERVER_INFO        BYEL "[Server] " CRESET
# define SERVER_KO          BRED "[Server] " CRESET

# define ENTER_PASS_FIRST   BRED "You have to enter the password first using the PASS command." CRESET

#endif
