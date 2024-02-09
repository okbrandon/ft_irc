/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:19:46 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/09 10:22:29 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/NickCommand.hpp"

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
	std::string	nickname;

	if (!this->_user->hasSentPassword())
		throw ENTER_PASS_FIRST;
	if (this->_args.size() < 2)
		throw ERR_NONICKNAMEGIVEN;

	nickname = this->_args[1];
	if (!this->_isValidNickname(nickname))
		throw ERR_ERRONEUSNICKNAME(nickname);
	if (!this->_server->isNicknameAvailable(nickname))
		throw ERR_NICKNAMEINUSE(nickname);
	
	this->_user->setNickname(nickname);
	this->_user->addSendBuffer(": You are now nicked as ");
	this->_user->addSendBuffer(BCYN + nickname + CRESET "\r\n");
}
