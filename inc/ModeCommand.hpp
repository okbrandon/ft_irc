/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:44 by evmorvan          #+#    #+#             */
/*   Updated: 2024/02/26 09:57:45 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODECOMMAND_HPP
# define MODECOMMAND_HPP

# include "IRCDepends.hpp"

class ModeCommand : public ACommand {

	public:
		ModeCommand(void);
		~ModeCommand(void);

		void	execute(void) const;

};

#endif
