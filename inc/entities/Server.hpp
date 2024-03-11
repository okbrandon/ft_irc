/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:49:59 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 17:55:41 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "../IRCDepends.hpp"

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
		std::string						_lastLogin;
		std::string						_lastLogout;
		Executor						*_executor;

		/* Private constructor */
		Server(void);
		Server(const Server &origin);

		/* Private functions */
		std::string	_createTimestamp(void);
		int			_createSocket(void);
		bool		_createUserConnection(void);
		bool		_handleUserConnection(std::vector<pollfd>::iterator &it);
		bool		_handlePollOut(std::vector<pollfd>::iterator &it);
		void		_addUser(int fd, struct sockaddr_in userAddr);
		void		_removeUser(int fd, std::vector<pollfd>::iterator &it);
		void		_removeUserFromChannels(int fd);
		void		_removeEmptyChannels(void);
		void		_parseReceived(int fd, std::string message);
		void		_printServerInfos(void);

		/* Overloaded operators */
		Server	&operator=(const Server &origin);

	public:
		/* Constructors & Destructors */
		Server(const std::string &hostname, int port, const std::string &password);
		~Server(void);

		/* Functions */
		void	run(void);
		void	broadcast(std::string message);
		void	addChannel(Channel *channel);
		void	removeChannel(std::string channelName);
		User	*findUserByFd(int fd);
		User	*findUserByName(std::string name);
		Channel	*findChannelByName(std::string name);
		Channel	*findChannelByUser(User *user);
		bool	isNicknameAvailable(std::string nickname);

		/* Getters & Setters */
		std::string	getCreationDate(void) const;
		std::string	getHostname(void) const;
		std::string	getPassword(void) const;
		int			getPort(void) const;
		int			getListenerSocket(void) const;

};

#endif
