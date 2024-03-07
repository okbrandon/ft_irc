/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:55:24 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/07 12:02:20 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "IRCDepends.hpp"

class Utils {

	public:
		static std::string	getCompletionJson(const std::string& nickname, const std::string& channel, const std::string& message);
		template <class T> static std::string	toString(const T &value) {
			std::ostringstream oss;

			oss << value;
			return (oss.str());
		}

};

#endif
