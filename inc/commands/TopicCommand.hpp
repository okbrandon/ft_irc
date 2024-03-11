/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:57:48 by evmorvan          #+#    #+#             */
/*   Updated: 2024/03/11 17:55:23 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPICCOMMAND_HPP
# define TOPICCOMMAND_HPP

# include "../IRCDepends.hpp"

class TopicCommand : public ACommand {

	public:
		TopicCommand(void);
		~TopicCommand(void);

		void	execute(void) const;

};

#endif
