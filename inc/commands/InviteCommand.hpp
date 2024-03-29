/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:37 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/11 17:54:50 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITECOMMAND_HPP
# define INVITECOMMAND_HPP

# include "../IRCDepends.hpp"

class InviteCommand : public ACommand {

	public:
		InviteCommand(void);
		~InviteCommand(void);

		void	execute(void) const;

};

#endif
