/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCLogger.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:16:53 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/28 10:28:30 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCLOGGER_HPP
# define IRCLOGGER_HPP

# include "IRCDepends.hpp"

class IRCLogger {

	private:
		std::deque<std::string>	_queuedMessages;

		IRCLogger(void);
		IRCLogger(const IRCLogger &origin);
		
		IRCLogger	&operator=(const IRCLogger &origin);

	public:
		~IRCLogger(void);

		void	queue(std::string message);
		void	printQueue(void);
		void	destroy(void);

		static IRCLogger	*getInstance(void);
	
};

#endif
