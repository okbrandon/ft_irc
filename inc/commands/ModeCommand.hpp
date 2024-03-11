/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:44 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/11 17:55:00 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP

# include "../IRCDepends.hpp"

class ModeCommand : public ACommand {

	private:
		bool		_addMode(Channel *channel) const;
		bool		_removeMode(Channel *channel) const;

	public:
		ModeCommand(void);
		~ModeCommand(void);

		void	execute(void) const;

};

#endif
