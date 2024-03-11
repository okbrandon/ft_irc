/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:18:24 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 17:55:04 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "../IRCDepends.hpp"

class NickCommand : public ACommand {

	private:
		bool	_isValidCharacter(char c) const;
		bool	_isValidNickname(std::string nickname) const;

	public:
		NickCommand(void);
		~NickCommand(void);

		void	execute(void) const;

};

#endif
