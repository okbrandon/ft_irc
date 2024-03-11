/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:19:46 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/11 17:56:52 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/commands/NickCommand.hpp"

NickCommand::NickCommand(void) : ACommand("NICK") {}

NickCommand::~NickCommand(void) {}

bool	NickCommand::_isValidCharacter(char c) const {
	return (c != ' ' && c != '*' && c != '?' && c != '!' && c != ',' && c != '@' && c != '.');
}

bool	NickCommand::_isValidNickname(std::string nickname) const {
	if (nickname.at(0) == '#' || nickname.at(0) == ':' || nickname.at(0) == '$')
		return (false);
	for (size_t i = 0; i < nickname.length(); i++) {
		if (!this->_isValidCharacter(nickname.at(i)))
			return (false);
	}
	return (true);
}

void	NickCommand::execute(void) const {
	std::string	userId = USER_IDENTIFIER(this->_user->getNickname(), this->_user->getUsername());
	std::string	nickname;
	static int	i;

	if (!this->_user->hasSentPassword())
		throw ENTER_PASS_FIRST;
	if (this->_args.size() < 2)
		throw ERR_NONICKNAMEGIVEN(userId, this->_user->getNickname());

	nickname = this->_args[1];
	if (!this->_isValidNickname(nickname))
		throw ERR_ERRONEUSNICKNAME(userId, this->_user->getNickname(), nickname);
	if (!this->_server->isNicknameAvailable(nickname)) {
		if (this->_user->isRegistered())
			throw ERR_NICKNAMEINUSE(userId, this->_user->getNickname(), nickname);

		nickname.append(Utils::toString(++i));
		/* Start of debug */
		IRCLogger::getInstance()->queue(Utils::toString(SERVER_INFO) \
			+ "User asked for nickname '" BRED + this->_args[1] \
			+ CRESET "' but got '" BRED + nickname \
			+ CRESET "'...\n");
		/* End of debug */
	}

	this->_user->setNickname(nickname);
	this->_user->addSendBuffer(": You are now nicked as ");
	this->_user->addSendBuffer(BCYN + nickname + CRESET "\r\n");
}
