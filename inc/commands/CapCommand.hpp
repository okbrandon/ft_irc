/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CapCommand.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:39:47 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 17:54:47 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAPCOMMAND_HPP
# define CAPCOMMAND_HPP

# include "../IRCDepends.hpp"

class CapCommand : public ACommand {

	public:
		CapCommand(void);
		~CapCommand(void);

		void	execute(void) const;

};

#endif
