/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCNumReplies.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:30:22 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/13 15:56:41 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCNUMREPLIES_HPP
# define IRCNUMREPLIES_HPP

/*
 * All references can be found at:
 *  - https://www.alien.net.au/irc/irc2numerics.html
 *  - http://www.iprelax.fr/irc/irc_rfcus6.php
*/

# define USER_IDENTIFIER(nickname, username) (":" + nickname + "!" + username + "@localhost")

# define RPL_WELCOME(user_id, nickname) (user_id + " 001 " + nickname + " :Welcome to the Internet Relay Network " + user_id + "\r\n")
# define RPL_YOURHOST(user_id, nickname, servername, version) (user_id + " 002 " + nickname + " :Your host is " + servername + " (localhost), running version " + version + "\r\n")
# define RPL_CREATED(user_id, nickname, date) (user_id + " 003 " + nickname + " :This server was created " + date + "\r\n")
# define RPL_TOPIC(user_id, nickname, channel, topic) (user_id + " 332 " + nickname + " " + channel + " :" + topic + "\r\n")
# define RPL_NOTOPIC(user_id, nickname, channel) (user_id + " 331 " + nickname + " " + channel + " :No topic is set." + "\r\n")
# define RPL_NAMREPLY(user_id, nickname, channelMode, channel, userList) (user_id + " 353 " + nickname + " " + channelMode + " " + channel + " :" + userList + "\r\n")
# define RPL_ENDOFNAMES(user_id, nickname, channel) (user_id + " 366 " + nickname + " " + channel + " :End of /NAMES list" + "\r\n")
# define RPL_INVITING(user_id, nickname, channel, requested) (user_id + " 341 " + nickname + " " + channel + " " + requested + "\r\n")
# define RPL_CHANNELMODEIS(user_id, nickname, channel, mode) (user_id + " 324 " + nickname + " " + channel + " " + mode + "\r\n") // removed params
# define RPL_UMODEIS(user_id, nickname, mode) (user_id + " 221 " + nickname + " " + mode + "\r\n")

# define ERR_NOSUCHNICK(user_id, nickname, requested) (user_id + " 401 " + nickname + " " + requested + " :No such nick/channel" + "\r\n")
# define ERR_NOSUCHCHANNEL(user_id, nickname, channel) (user_id + " 403 " + nickname + " " + channel + " :No such channel" + "\r\n")
# define ERR_USERNOTINCHANNEL(user_id, nickname, channel, requested) (user_id + " 441 " + nickname + " " + channel + " " + requested + " :They aren't on that channel" + "\r\n")
# define ERR_NORECIPIENT(user_id, nickname, command) (user_id + " 411 " + nickname + " " + command + " :No recipient given" + "\r\n")
# define ERR_NOTONCHANNEL(user_id, nickname, channel) (user_id + " 442 " + nickname + " " + channel + " :You're not on that channel" + "\r\n")
# define ERR_NEEDMOREPARAMS(user_id, nickname, command) (user_id + " 461 " + nickname + " " + command + " :Not enough parameters" + "\r\n")
# define ERR_ALREADYREGISTRED(user_id, nickname) (user_id + " 462 " + nickname + " :You may not reregister" + "\r\n")
# define ERR_PASSWDMISMATCH(user_id, nickname) (user_id + " 464 " + nickname + " :Password incorrect" + "\r\n")
# define ERR_NONICKNAMEGIVEN(user_id, nickname) (user_id + " 431 " + nickname + " :No nickname given" + "\r\n")
# define ERR_ERRONEUSNICKNAME(user_id, nickname, requested) (user_id + " 432 " + nickname + " " + requested + " :Erroneus nickname" + "\r\n")
# define ERR_NICKNAMEINUSE(user_id, nickname, requested) (user_id + " 433 " + nickname + " " + requested + " :Nickname is already in use" + "\r\n")
# define ERR_CHANNELISFULL(user_id, nickname, channel) (user_id + " 471 " + nickname + " " + channel + " :Cannot join channel (+l)" + "\r\n")
# define ERR_UNKNOWNMODE(user_id, nickname, modeChar) (user_id + " 472 " + nickname + " " + modeChar + " :is unknown mode char to me" + "\r\n")
# define ERR_INVITEONLYCHAN(user_id, nickname, channel) (user_id + " 473 " + nickname + " " + channel + " :Cannot join channel (+i)" + "\r\n")
# define ERR_BADCHANMASK(user_id, nickname, channel) (user_id + " 476 " + nickname + " " + channel + " :Incorrect format" + "\r\n")
# define ERR_BADCHANNELKEY(user_id, nickname, channel) (user_id + " 475 " + nickname + " " + channel + " :Cannot join channel (+k)" + "\r\n")
# define ERR_CHANOPRIVSNEEDED(user_id, nickname, channel) (user_id + " 482 " + nickname + " " + channel + " :You're not channel operator" + "\r\n")

#endif
