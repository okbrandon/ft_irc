/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:14:05 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 17:54:54 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "../IRCDepends.hpp"

class JoinCommand : public ACommand {

	private:
		std::string	_getStringifiedUsers(Channel *channel) const;
		std::string	_getChannelMode(Channel *channel) const;

	public:
		JoinCommand(void);
		~JoinCommand(void);

		void	execute(void) const;

};

#endif
