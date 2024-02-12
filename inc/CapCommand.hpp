/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CapCommand.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:39:47 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/12 16:48:09 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAPCOMMAND_HPP
# define CAPCOMMAND_HPP

# include "IRCDepends.hpp"

class CapCommand : public ACommand {

	public:
		CapCommand(void);
		~CapCommand(void);

		void	execute(void) const;

};

#endif
