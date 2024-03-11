/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:13:07 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 17:55:17 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSGCOMMAND_HPP
# define PRIVMSGCOMMAND_HPP

# include "../IRCDepends.hpp"

class PrivmsgCommand : public ACommand {

	private:
		bool		_sendChannelMessage(std::string channelName, std::string message) const;
		bool		_sendUserMessage(std::string nickName, std::string message) const;
		std::string	_getMessage(void) const;

	public:
		PrivmsgCommand(void);
		~PrivmsgCommand(void);

		void	execute(void) const;

};

#endif
