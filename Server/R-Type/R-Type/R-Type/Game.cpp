#include "Game.hpp"

Game::Game(Player *p, int id): id(id), player1(p), player2(0), player3(0), player4(0)
{ }

Game::~Game(void)
{ }

void	Game::setId(int _id)
{
	id = _id;
}

void	Game::setPlayer(Player *_player, int id)
{
	if (id == 0)
		player1 = _player;
	else if (id == 1)
		player2 = _player;
	else if (id == 2)
		player3 = _player;
	else if (id == 3)
		player4 = _player;
}

void	Game::setPlayer(Player *_player, RTProtocol::Identifier id)
{
	if (id.Id == RTProtocol::PLAYER_1)
		player1 = _player;
	else if (id.Id == RTProtocol::PLAYER_2)
		player2 = _player;
	else if (id.Id == RTProtocol::PLAYER_3)
		player3 = _player;
	else if (id.Id == RTProtocol::PLAYER_4)
		player4 = _player;
}

int		Game::getId(void) const
{
	return id;
}

Player	*Game::getPlayer(int id) const
{
	if (id == 0)
		return player1;
	else if (id == 1)
		return player2;
	else if (id == 2)
		return player3;
	else if (id == 3)
		return player4;
	return 0;
}

Monster	*Game::getMonster(int id) const
{
	return monsters[id];
}

std::vector<Monster *>	Game::getMonsters(void) const
{
	return monsters;
}

int		Game::getEmptySlot() const
{
	if (player1 == 0)
		return (0);
	else if (player2 == 0)
		return (1);
	else if (player3 == 0)
		return (2);
	else if (player4 == 0)
		return (3);
	return (-1);
}
