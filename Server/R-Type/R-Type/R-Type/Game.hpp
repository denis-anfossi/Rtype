#ifndef		GAME_HPP
#define		GAME_HPP

#ifdef __linux__
#include	"DLL/LinuxDynLib.hpp"
#else
#include	"DLL\WindowsDynLib.hpp"
#endif
#include	"Player.hpp"
#include	"DLL/IMonster.hpp"
#include	<vector>

class Game
{
public:
	Game(Player *p, int id);
	~Game(void);

	void	setId(int _id);
	void	setPlayer(Player *_player, int id);
	void	setPlayer(Player *_player, RTProtocol::Identifier id);
	void	addMonster(RTProtocol::MONSTER_TYPE type);
	void	deleteMonster(int id);
	int		getId(void) const;
	Player	*getPlayer(int id) const;
	IMonster	*getMonster(int id) const;
	std::vector<IMonster *>	getMonsters(void) const;
	int		getEmptySlot() const;
private:
	int		id;
	Player	*player1;
	Player	*player2;
	Player	*player3;
	Player	*player4;
	std::vector<IMonster *>	monsters;
	IDynLib	*sharedLib;
};

#endif		/* GAME_HPP */
