/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:49:59 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/29 11:37:57 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "IRCDepends.hpp"

// Retreiving global variable from main
extern bool	g_server_running;

/*
 * Soft-depending
 */
class User;
class Channel;
class Executor;

class Server {

	private:
		/* Attributes */
		std::vector<pollfd>				_polls;
		std::map<int, User>				_users;
		std::map<std::string, Channel*>	_channels;
		std::string						_creationDate;
		std::string						_hostname;
		std::string						_password;
		int								_port;
		int								_listenerSocket;
		Executor						*_executor;

		/* Private constructor */
		Server(void);

		/* Private functions */
		std::string	_createTimestamp(void);
		int			_createSocket(void);
		bool		_createUserConnection(void);
		bool		_handleUserConnection(std::vector<pollfd>::iterator &it);
		bool		_handlePollOut(std::vector<pollfd>::iterator &it);
		void		_addUser(int userSocket, struct sockaddr_in userAddr);
		void		_removeUser(int currentFd, std::vector<pollfd>::iterator &it);
		void		_parseReceived(int fd, std::string message);
		void		_printServerInfos(void);

	public:
		/* Constructors & Destructors */
		Server(const std::string &hostname, int port, const std::string &password);
		Server(const Server &origin);
		~Server(void);

		/* Functions */
		void	run(void);
		void	broadcast(std::string message);
		void	addChannel(Channel *channel);
		void	removeChannel(std::string channelName);
		User	*findUserByFd(int fd);
		User	*findUserByName(std::string name);
		Channel	*findChannelByName(std::string name);
		bool	isNicknameAvailable(std::string nickname);

		/* Getters & Setters */
		std::string	getCreationDate(void) const;
		std::string	getHostname(void) const;
		std::string	getPassword(void) const;
		int			getPort(void) const;
		int			getListenerSocket(void) const;

		/* Overloaded operators */
		Server	&operator=(const Server &origin);

};

#endif
