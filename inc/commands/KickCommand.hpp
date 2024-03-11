/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:40 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/11 17:54:57 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICKCOMMAND_HPP
# define KICKCOMMAND_HPP

# include "../IRCDepends.hpp"

class KickCommand : public ACommand {

	public:
		KickCommand(void);
		~KickCommand(void);

		void	execute(void) const;

};

#endif
