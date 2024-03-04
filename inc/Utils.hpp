/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:17:56 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/04 10:07:12 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "IRCDepends.hpp"

class Utils {

	private:	

	public:
		static int								stoi(std::string &s);
		static std::string						fixWidth(std::string str, int truncateAt);
		static std::string						removeEndOccurrence(std::string str, std::string find);
		static std::deque<std::string>			split(std::string message, std::string delimiters);
		template <class T> static std::string	toString(const T &value) {
			std::ostringstream oss;

			oss << value;
			return (oss.str());
		}

};

#endif
