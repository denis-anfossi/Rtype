#include "Player.hpp"

Player::Player(const struct sockaddr_in _rcv): rcv(_rcv), idGame(-1)
{ 
	RTProtocol::Identifier	id;

	id.Id = RTProtocol::NO_PLAY;
}

Player::~Player(void)
{ }

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