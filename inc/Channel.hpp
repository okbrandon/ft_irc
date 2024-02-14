/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:38:16 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/14 10:35:41 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "IRCDepends.hpp"

class User;

/*
 * Structure of an IRC channel
 * 
 * Name - Each channel has a unique name that identifies it. Channel names typically start with the # symbol, like #help or #linux.
 * Users - An IRC channel has multiple users connected to it, who can all participate in the chat. There is no limit on the number of users in a channel.
 * Modes - Channels have different modes that control things like if it's invite-only, moderated, private, etc. Channel operators can set these modes.
 * Topic - A channel topic provides a short description of what the channel is about. It's set by channel operators.
 * Channel operators - Also known as admins or ops. They manage the channel, set modes, kick or ban unruly users, appoint other ops, change the topic, etc. Operators are identified by the @ symbol next to their nick.
 * Conversation - The main purpose of a channel is interaction between users. All users can participate in conversations by sending public messages.
 * Limit - Max users
 * Key - Channel password
 */
class Channel {

	private:
		/* Attributes */
		std::string					_name;
		std::string					_key;
		std::string					_topic;
		std::vector<char>			_modes;
		std::vector<User*>			_users;
		std::vector<User*>			_operators;
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
		void	broadcast(std::string message);

		/* Getters */
		std::string					getName(void) const;
		std::string					getKey(void) const;
		std::string					getTopic(void) const;
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

		/* Setters */
		void	setKey(std::string key);
		void	setTopic(std::string topic);
		void	setLimit(unsigned int limit);
		void	setOwner(User *owner);

		/* Overloaded operators */
		Channel	&operator=(Channel const &origin);

};

#endif
