/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:37 by evmorvan          #+#    #+#             */
/*   Updated: 2024/02/26 09:58:43 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITECOMMAND_HPP
# define INVITECOMMAND_HPP

# include "IRCDepends.hpp"

class InviteCommand : public ACommand {

	public:
		InviteCommand(void);
		~InviteCommand(void);

		void	execute(void) const;

};

#endif
