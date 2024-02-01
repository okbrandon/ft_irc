/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:30:13 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/01 18:37:01 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include "IRCDepends.hpp"

class ACommand {

	protected:
		std::string				_name;
		std::list<std::string>	_args;
		User					*_user;
		Server					*_server;

	public:
		ACommand(void);
		ACommand(ACommand const &origin);
		virtual ~ACommand(void);

		std::string	getName(void) const;

		void	setArgs(std::list<std::string> args);
		void	setUser(User *user);
		void	setServer(Server *server);

		virtual void	execute(void) const = 0;

		ACommand	&operator=(ACommand const &origin);

};

#endif