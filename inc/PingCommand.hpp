/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:19:12 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/09 17:22:54 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PINGCOMMAND_HPP
# define PINGCOMMAND_HPP

# include "IRCDepends.hpp"

class PingCommand : public ACommand {

	public:
		PingCommand(void);
		~PingCommand(void);

		void	execute(void) const;

};

#endif
