/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:38:16 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/13 10:54:32 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../IRCDepends.hpp"

class User;

class Channel {

	private:
		/* Attributes */
		std::string					_name;
		std::string					_key;
		std::string					_topic;
		std::vector<char>			_modes;
		std::vector<User*>			_users;
		std::vector<User*>			_operators;
		std::vector<std::string>	_inviteList;
		std::vector<std::string>	_conversation;
		unsigned int				_limit;
		User						*_owner;

		/* Private constructors & destructors */
		Channel(void);

	public:
		/* Constructors & Destructors */
		Channel(std::string name);
		Channel(Channel const &origin);
		~Channel(void);

		/* Functions */
		void	addMode(char mode);
		void	removeMode(char mode);
		void	addUser(User *user);
		void	removeUser(User *user);
		void	addOperator(User *user);
		void	removeOperator(User *user);
		void	addInvitation(User *user);
		void	removeInvitation(User *user);
		void	broadcast(std::string message);
		void	excludeBroadcast(std::string message, User *excluded);

		/* Getters */
		std::string					getName(void) const;
		std::string					getKey(void) const;
		std::string					getTopic(void) const;
		std::string					getModeString(void) const;
		std::vector<char>			getModes(void) const;
		std::vector<User*>			getUsers(void) const;
		std::vector<User*>			getOperators(void) const;
		std::vector<std::string>	getConversation(void) const;
		unsigned int				getLimit(void) const;
		User						*getOwner(void) const;
		bool						isOperator(User *user);
		bool						isInChannel(User *user);
		bool						isKeyProtected(void) const;
		bool						hasMode(char mode) const;
		bool						isInvited(User *user) const;

		/* Setters */
		void	setKey(std::string key);
		void	setTopic(std::string topic);
		void	setLimit(unsigned int limit);
		void	setOwner(User *owner);

		/* Overloaded operators */
		Channel	&operator=(Channel const &origin);

};

#endif
