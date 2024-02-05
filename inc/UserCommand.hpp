/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:01:16 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/05 10:33:38 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERCOMMAND_HPP
# define USERCOMMAND_HPP

# include "IRCDepends.hpp"

class UserCommand : public ACommand {

	private:
		std::string	_extractRealname(std::deque<std::string> args) const;

	public:
		UserCommand(void);
		~UserCommand(void);

		void	execute(void) const;
	
};

#endif