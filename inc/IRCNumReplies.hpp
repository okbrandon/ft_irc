/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCNumReplies.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:30:22 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/05 09:14:00 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCNUMREPLIES_HPP
# define IRCNUMREPLIES_HPP

/*
 * All references can be found at:
 *  - https://www.alien.net.au/irc/irc2numerics.html
 *  - http://www.iprelax.fr/irc/irc_rfcus6.php
*/

// This is the stringificator
#define STR(str) #str
#define STRING(str) STR(str)

# define USER_IDENTIFIER(nickname, username) (":" + nickname + "!" + username "@localhost")

# define RPL_WELCOME(nickname, user_id) (":localhost 001 " + nickname + " :Welcome to the Internet Relay Network " + user_id + "\r\n")
# define RPL_YOURHOST(user, servername, version) (":localhost 002 " + user + " :Your host is " + servername + " (localhost), running version " + version + "\r\n")
# define RPL_CREATED(user, date) (":localhost 003 " + user + " :This server was created " + date + "\r\n")

# define ERR_NEEDMOREPARAMS(command) ("461 * " + command + ": Not enough parameters" + "\r\n")
# define ERR_ALREADYREGISTRED "462 * : You're already registered\r\n"
# define ERR_PASSWDMISMATCH "464 * : Password incorrect\r\n"
# define ERR_NONICKNAMEGIVEN "431 * : No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nickname) ("432 * : " + nickname + " : Erroneus nickname" + "\r\n")
# define ERR_NICKNAMEINUSE(nickname) ("433 * : " + nickname + " : Nickname is already in use" + "\r\n")

#endif