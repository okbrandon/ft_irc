/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:49:59 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/01/16 17:21:02 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "IRCDepends.hpp"

class Server {

	private:
		/* Attributes */
		std::vector<pollfd>	_polls;
		std::string			_hostname;
		std::string			_password;
		int					_port;
		int					_listenerSocket;

		/* Private constructor */
		Server(void);

		/* Private functions */
		int	_createSocket(void);

	public:
		/* Constructors & Destructors */
		Server(const std::string &hostname, int port, const std::string &password);
		Server(const Server &origin);
		~Server(void);

		/* Functions */
		void	run(void);

		/* Getters & Setters */
		std::string	getHostname(void) const;
		std::string	getPassword(void) const;
		int			getPort(void) const;
		int			getListenerSocket(void) const;

		/* Overloaded operators */
		Server	&operator=(const Server &origin);

};

#endif