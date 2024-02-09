/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:17:56 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/09 15:43:26 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "IRCDepends.hpp"

class Utils {

	private:	

	public:
		static int								stoi(std::string &s);
		static std::deque<std::string>			splitArguments(std::string &message);
		static std::deque<std::string>			splitCommands(std::string &message);
		template <class T> static std::string	toString(const T &value) {
			std::ostringstream oss;

			oss << value;
			return (oss.str());
		}

};

#endif
