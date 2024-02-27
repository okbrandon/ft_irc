/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:40 by evmorvan          #+#    #+#             */
/*   Updated: 2024/02/26 09:57:41 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICKCOMMAND_HPP
# define KICKCOMMAND_HPP

# include "IRCDepends.hpp"

class KickCommand : public ACommand {

	public:
		KickCommand(void);
		~KickCommand(void);

		void	execute(void) const;

};

#endif
