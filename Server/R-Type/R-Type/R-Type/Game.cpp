#include "Game.hpp"

Game::Game(Player *p, int id): id(id), player1(p), player2(0), player3(0), player4(0)
{
#ifdef __linux__
	sharedLib = new LinuxDynLib();
#else
	sharedLib = new WindowsDynLib();
#endif
/*	
	addMonster(RTProtocol::MONSTER_TYPE1);
	if (monsters.size() > 0)
		std::cout << monsters[0]->getX() << std::endl;
*/
}

Game::~Game(void)
{
	for (unsigned int i = 0; i < monsters.size(); ++i)
		delete monsters[i];
	delete sharedLib;
}

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

void	Game::addMonster(RTProtocol::MONSTER_TYPE type)
{
  std::string	libName;
  if (type == RTProtocol::MONSTER_TYPE1)
    libName = "DLL/CreateMonsterFirstTypeDLL";
  else if (type == RTProtocol::MONSTER_TYPE2)
    libName = "DLL/CreateMonsterFirstTypeDLL";
  
#ifdef __linux__
  libName += ".so";
#else
  libName += ".dll";
#endif
  
  IMonster	*(*external_creator)(int, int);
  
  if (sharedLib->openLib(libName) != NULL)
    {
      sharedLib->setSymbolName("getInstanceDLL");
      external_creator = reinterpret_cast<IMonster *	(*)(int, int)>(sharedLib->dlSymb());
      monsters.push_back(external_creator(100, 100));
      sharedLib->closeLib();
    }
}

void	Game::deleteMonster(int id)
{
  
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

IMonster	*Game::getMonster(int id) const
{
	return monsters[id];
}

std::vector<IMonster *>	Game::getMonsters(void) const
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
