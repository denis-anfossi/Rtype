#include "Player.hpp"

Player::Player(const struct sockaddr_in _rcv): rcv(_rcv), idGame(-1)
{ 
	RTProtocol::Identifier	id;

	id.Id = RTProtocol::NO_PLAY;
}

Player::~Player(void)
{ }

void	Player::setId(int _id)
{
	if (_id == 0)
		id.Id = RTProtocol::PLAYER_1;
	else if (_id == 1)
		id.Id = RTProtocol::PLAYER_2;
	else if (_id == 2)
		id.Id = RTProtocol::PLAYER_3;
	else if (_id == 3)
		id.Id = RTProtocol::PLAYER_4;
}

void	Player::setId(RTProtocol::Identifier _id)
{
	id = _id;
}

const struct sockaddr_in	Player::getSockaddr(void) const
{
	return rcv;
}

RTProtocol::Identifier	Player::getId() const
{
	return id;
}

void	Player::setIdGame(int _idGame)
{
	idGame = _idGame;
}

int		Player::getIdGame(void) const
{
	return idGame;
}