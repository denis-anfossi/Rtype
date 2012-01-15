#ifndef		GAME_HPP
#define		GAME_HPP

#include	"Player.hpp"
#include	"DLL/Monster.h"
#include	<vector>

class Game
{
public:
	Game(Player *p, int id);
	~Game(void);

	void	setId(int _id);
	void	setPlayer(Player *_player, int id);
	void	setPlayer(Player *_player, RTProtocol::Identifier id);
	int		getId(void) const;
	Player	*getPlayer(int id) const;
	Monster	*getMonster(int id) const;
	std::vector<Monster *>	getMonsters(void) const;
	int		getEmptySlot() const;
private:
	int		id;
	Player	*player1;
	Player	*player2;
	Player	*player3;
	Player	*player4;
	std::vector<Monster *>	monsters;
};

#endif		/* GAME_HPP */