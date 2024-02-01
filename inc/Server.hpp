/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:49:59 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/01 17:14:59 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "IRCDepends.hpp"

// Retreiving global variable from main
extern bool	g_server_running;

/*
 * Soft-depending User class.
 */
class User;

class Server {

	private:
		/* Attributes */
		std::vector<pollfd>		_polls;
		std::map<int, User>		_users;
		std::string				_creationDate;
		std::string				_hostname;
		std::string				_password;
		int						_port;
		int						_listenerSocket;

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

	public:
		/* Constructors & Destructors */
		Server(const std::string &hostname, int port, const std::string &password);
		Server(const Server &origin);
		~Server(void);

		/* Functions */
		void		run(void);	
		User		*findUserByFd(int fd);

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