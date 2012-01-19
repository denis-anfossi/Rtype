#include "Game.hpp"

Game::Game(Player *p, int id): id(id), player1(p), player2(0), player3(0), player4(0), idMonsters(0)
{
#ifdef __linux__
	idMutex = new UnixMutex();
	players = new UnixMutex();
	monstersMutex = new UnixMutex();
#else
	idMutex = new WinMutex();
	playersMutex = new WinMutex();
	monstersMutex = new WinMutex();
#endif

	idMutex->init();
	playersMutex->init();
	monstersMutex->init();

	gettimeofday(&old, NULL);
	gettimeofday(&old2, NULL);
	gameTimer = 1;
	gameTimer2 = 700000;
	old.tv_sec += 2;
	old2.tv_sec += 1;
}

Game::~Game(void)
{
	monstersMutex->lock();
	for (unsigned int i = 0; i < monsters.size(); ++i)
		delete monsters[i];
	monstersMutex->unlock();

	idMutex->destroy();
	playersMutex->destroy();
	monstersMutex->destroy();

	delete	idMutex;
	delete	playersMutex;
	delete	monstersMutex;
}


void	Game::update2()
{
	monstersMutex->lock();
	for (std::vector<IMonster *>::iterator it = monsters.begin(); it != monsters.end(); )
	{
		if ((*it)->getX() < -100 || (*it)->getY() < -100 || (*it)->getY() > 600)
			it = monsters.erase(it);
		else
			++it;
	}
	monstersMutex->unlock();
}

void	Game::update(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if ((old.tv_usec >= now.tv_usec && old.tv_sec == now.tv_sec) || old.tv_sec < now.tv_sec)
	{
		addMonster(RTProtocol::MONSTER_TYPE1);
		addMonster(RTProtocol::MONSTER_TYPE2);
		addMonster(RTProtocol::MONSTER_TYPE1);
		addMonster(RTProtocol::MONSTER_TYPE2);
		old.tv_sec = now.tv_sec + gameTimer;
		old.tv_usec = now.tv_usec;
	}
	if ((old2.tv_usec >= now.tv_usec && old2.tv_sec == now.tv_sec) || old2.tv_sec < now.tv_sec)
	{
		monstersMutex->lock();
		for (std::vector<IMonster *>::iterator it = monsters.begin(); it != monsters.end(); ++it)
		{
			(*it)->update();
			if ((*it)->getX() < -100 || (*it)->getY() < -100 || (*it)->getY() > 600)
				(*it)->setLife(0);
		}
		old2.tv_sec = now.tv_sec;
		old2.tv_usec = now.tv_usec + gameTimer2;
		monstersMutex->unlock();
	}
}

void	Game::setId(int _id)
{
	AutoMutex	am(idMutex);
	id = _id;
}

void	Game::setPlayer(Player *_player, int id)
{
	AutoMutex	am(playersMutex);
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
	AutoMutex	am(playersMutex);
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
	IMonster	*(*external_creator)(int, int);  
	Server *s = Server::getInstance();

//	std::cout << "ADD MONSTER" << std::endl;
	if (type == RTProtocol::MONSTER_TYPE1)
		external_creator = reinterpret_cast<IMonster *	(*)(int, int)>(s->getSharedLibMonsterFirstType()->dlSymb());
	else if (type == RTProtocol::MONSTER_TYPE2)
		external_creator = reinterpret_cast<IMonster *	(*)(int, int)>(s->getSharedLibMonsterSecondType()->dlSymb());
	monstersMutex->lock();
	monsters.push_back(external_creator(100, 100));
	monsters.back()->setId(idMonsters++);
	monstersMutex->unlock();
}

void	Game::deleteMonster(int id)
{
	AutoMutex	am(monstersMutex);
	for (std::vector<IMonster *>::iterator it = monsters.begin(); it != monsters.end(); )
		if ((*it)->getId() == id)
		{
			delete *it;
			it = monsters.erase(it);
		}
		else
			++it;
}

int		Game::getId(void) const
{
	AutoMutex	am(idMutex);
	return id;
}

Player	*Game::getPlayer(int id) const
{
	AutoMutex	am(playersMutex);
	if (id == 0)
		return player1;
	else if (id == 1)
		return player2;
	else if (id == 2)
		return player3;
	else if (id == 3)
		return player4;
	return NULL;
}

IMonster	*Game::getMonster(int id) const
{
	AutoMutex	am(monstersMutex);
	return monsters[id];
}

std::vector<IMonster *>	Game::getMonsters(void) const
{
	AutoMutex	am(monstersMutex);
	return monsters;
}

int		Game::getEmptySlot() const
{
	AutoMutex	am(playersMutex);
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
