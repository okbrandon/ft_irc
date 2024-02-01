/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCNumReplies.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:30:22 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/01 18:30:23 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCNUMREPLIES_HPP
# define IRCNUMREPLIES_HPP

/*
 * All references can be found at:
 *  - https://www.alien.net.au/irc/irc2numerics.html
*/

// This is the stringificator
#define STR(str) #str
#define STRING(str) STR(str)

# define USER_IDENTIFIER(nickname, username) (":" + nickname + "!" + username "@localhost")

// 001 	RPL_WELCOME 	RFC2812 	:Welcome to the Internet Relay Network <nick>!<user>@<host> 
# define RPL_WELCOME(nickname, user_id) (":localhost 001 " + nickname + " :Welcome to the Internet Relay Network " + user_id + "\r\n")
// 002 	RPL_YOURHOST 	RFC2812 	:Your host is <servername>, running version <version> 
# define RPL_YOURHOST(user, servername, version) (":localhost 002 " + user + " :Your host is " + servername + " (localhost), running version " + version + "\r\n")
// 003 	RPL_CREATED 	RFC2812 	:This server was created <date>
# define RPL_CREATED(user, date) (":localhost 003 " + user + " :This server was created " + date + "\r\n")

#endif