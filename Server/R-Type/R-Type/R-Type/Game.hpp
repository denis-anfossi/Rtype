#ifndef		GAME_HPP
#define		GAME_HPP

#include	"Player.hpp"
#include	"DLL/IMonster.hpp"
#include	"AutoMutex.hpp"
#include	"Server.hpp"
#include	<vector>

class Server;

class Game
{
public:
  Game(Player *p, int id);
  ~Game(void);

  void				update();
  void				update2();
  void				setId(int _id);
  void				setPlayer(Player *_player, int id);
  void				setPlayer(Player *_player, RTProtocol::Identifier id);
  void				addMonster(RTProtocol::MONSTER_TYPE type);
  void				deleteMonster(unsigned int id);
  int				getId(void) const;
  Player			*getPlayer(int id) const;
  IMonster			*getMonster(int id) const;
  std::vector<IMonster *>	getMonsters(void) const;
  int				getEmptySlot() const;
  void				checkCollision();
  void				checkCo(Player *p);
  bool				checkCol(int x, int y, int width, int height);

  IMutex			*idMutex;
  IMutex			*playersMutex;
  IMutex			*monstersMutex;
private:
  int				id;
  Player			*player1;
  Player			*player2;
  Player			*player3;
  Player			*player4;
  std::vector<IMonster *>	monsters;
  struct timeval	old;
  struct timeval	old2;
  long			gameTimer;
  int			idMonsters;
  int			status;
};

#endif		/* GAME_HPP */
