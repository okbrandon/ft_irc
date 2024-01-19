/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:57:15 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/01/19 15:06:03 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "IRCDepends.hpp"

class User {

	private:
		/* Attributes */
		std::string	_host;
		std::string	_nickname;
		std::string	_username;
		int			_port;
		int			_socket;
		bool		_registered;
		bool		_sentPassword;

		/* Private constructor */
		User(void);

	public:
		/* Constructors & Destructors */
		User(std::string &host, int port, int socket);
		User(User const &origin);
		~User(void);

		/* Functions */
		void	tryRegister(void);
		void	sendMessage(std::string message);

		/* Getters & Setters */
		std::string	getHost(void) const;
		std::string	getNickname(void) const;
		std::string	getUsername(void) const;
		int			getPort(void) const;
		int			getSocket(void) const;
		bool		isRegistered(void) const;
		bool		hasSentPassword(void) const;
		void		setNickname(std::string &nickname);
		void		setUsername(std::string &username);

		/* Overloaded operators */
		User	&operator=(User const &origin);

};

#endif