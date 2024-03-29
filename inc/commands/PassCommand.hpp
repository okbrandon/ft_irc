/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:49:44 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 17:55:10 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSCOMMAND_HPP
# define PASSCOMMAND_HPP

# include "../IRCDepends.hpp"

class PassCommand : public ACommand {

	public:
		PassCommand(void);
		~PassCommand(void);

		void	execute(void) const;

};

#endif
