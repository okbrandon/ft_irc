/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCNumReplies.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:30:22 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/23 11:47:00 by bsoubaig         ###   ########.fr       */
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

# define RPL_WELCOME(nickname, user_id) (":localhost 001 " + nickname + " :Welcome to the Internet Relay Network " + user_id + "\r\n")
# define RPL_YOURHOST(user, servername, version) (":localhost 002 " + user + " :Your host is " + servername + " (localhost), running version " + version + "\r\n")
# define RPL_CREATED(user, date) (":localhost 003 " + user + " :This server was created " + date + "\r\n")
# define RPL_TOPIC(user, channel, topic) (":localhost 332 " + user + " " + channel + " :" + topic + "\r\n")
# define RPL_NOTOPIC(user, channel) (":localhost 331 " + user + " " + channel + " :No topic is set." + "\r\n")
# define RPL_NAMREPLY(user, channelMode, channel, userList) ("353 " + user + " " + channelMode + " " + channel + " :" + userList + "\r\n")
# define RPL_ENDOFNAMES(user, channel) ("366 " + user + " " + channel + " :End of /NAMES list" + "\r\n")
# define RPL_INVITING(nickname, channel) (":localhost 341 " + nickname + " " + channel + "\r\n")

# define ERR_NOSUCHNICK(nickname) ("401 * " + nickname + " :No such nick/channel" + "\r\n")
# define ERR_NOSUCHCHANNEL(channel) ("403 * " + channel + " :No such channel" + "\r\n")
# define ERR_USERNOTINCHANNEL(channel, nickname) ("441 * " + channel + " " + nickname + " :They aren't on that channel" + "\r\n")
# define ERR_CHANOPRIVSNEEDED(channel) ("482 * " + channel + " :You're not channel operator" + "\r\n")
# define ERR_NORECIPIENT(command) ("411 * " + command + " :No recipient given" + "\r\n")
# define ERR_NOTONCHANNEL(channel) ("442 * " + channel + " :You're not on that channel" + "\r\n")
# define ERR_NEEDMOREPARAMS(command) ("461 * " + command + " :Not enough parameters" + "\r\n")
# define ERR_ALREADYREGISTRED "462 * :You may not reregister\r\n"
# define ERR_PASSWDMISMATCH "464 * :Password incorrect\r\n"
# define ERR_NONICKNAMEGIVEN "431 * :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nickname) ("432 * : " + nickname + " :Erroneus nickname" + "\r\n")
# define ERR_NICKNAMEINUSE(nickname) ("433 * : " + nickname + " :Nickname is already in use" + "\r\n")
# define ERR_CHANNELISFULL(channel) ("471 * : " + channel + " :Cannot join channel (+l)" + "\r\n")
# define ERR_INVITEONLYCHAN(channel) ("473 * : " + channel + " :Cannot join channel (+i)" + "\r\n")
# define ERR_BADCHANMASK(channel) ("476 * : " + channel + " :Incorrect format" + "\r\n")
# define ERR_BADCHANNELKEY(channel) ("475 * : " + channel + " :Cannot join channel (+k)" + "\r\n")

#endif
