/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:28:11 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 17:29:22 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUITCOMMAND_HPP
# define QUITCOMMAND_HPP

# include "IRCDepends.hpp"

class QuitCommand : public ACommand {

	public:
		QuitCommand(void);
		~QuitCommand(void);

		void	execute(void) const;

};

#endif
