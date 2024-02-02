/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:26:29 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/02 14:05:12 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_HPP
# define EXECUTOR_HPP

# include "ACommand.hpp"

class ACommand;

class Executor {

	private:
		Server					*_server;
		std::deque<ACommand*>	_commands;

		Executor(void);

		void	_registerCommands(void);
		bool	_isRegisteredCommand(std::string command);

	public:
		Executor(Server *server);
		Executor(Executor const &origin);
		~Executor(void);

		void	processCommand(User *user, std::deque<std::string> commandArgs);

		Executor	&operator=(Executor const &origin);

};

#endif