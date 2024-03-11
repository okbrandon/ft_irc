/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:03:34 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 16:08:24 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTCOMMAND_HPP
# define PARTCOMMAND_HPP

# include "IRCDepends.hpp"

class PartCommand : public ACommand {

	public:
		PartCommand(void);
		~PartCommand(void);

		void	execute(void) const;

};

#endif
