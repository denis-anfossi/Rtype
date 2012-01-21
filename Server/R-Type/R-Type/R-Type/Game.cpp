#include "Game.hpp"

Game::Game(Player *p, int id): id(id), player1(p), player2(0), player3(0), player4(0), idMonsters(0)
{
#ifdef __linux__
  idMutex = new UnixMutex();
  playersMutex = new UnixMutex();
  monstersMutex = new UnixMutex();
#else
  idMutex = new WinMutex();
  playersMutex = new WinMutex();
  monstersMutex = new WinMutex();
#endif

  idMutex->init();
  playersMutex->init();
  monstersMutex->init();

  status = 0;
  gettimeofday(&old, NULL);
  gettimeofday(&old2, NULL);
  gameTimer = 5;
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
  checkCollision();
  monstersMutex->lock();
  for (std::vector<IMonster *>::iterator it = monsters.begin(); it != monsters.end(); )
    {
      (*it)->update2();
      if ((*it)->getX() < -100 || (*it)->getY() < -100 || (*it)->getY() > 620)
	it = monsters.erase(it);
      else if ((*it)->getLife() == 0)
	it = monsters.erase(it);
      else
	++it;
    }
  monstersMutex->unlock();
  playersMutex->lock();
  if (player1)
    player1->update2();
  if (player2)
    player2->update2();
  if (player3)
    player3->update2();
  if (player4)
    player4->update2();
  playersMutex->unlock();
}

void	Game::update(void)
{
  struct timeval	now;

  gettimeofday(&now, NULL);
  if (status == 0)
    {
      if ((old.tv_usec >= now.tv_usec && old.tv_sec + gameTimer == now.tv_sec) ||
	  old.tv_sec + gameTimer < now.tv_sec)
	{
	  addMonster(RTProtocol::MONSTER_TYPE1);
	  addMonster(RTProtocol::MONSTER_TYPE2);
	  old.tv_sec = now.tv_sec;
	  old.tv_usec = now.tv_usec;
	}
      if (old2.tv_sec + 30 <= now.tv_sec)
	{
	  status = 1;
	  addMonster(RTProtocol::MONSTER_BOSS);
	}
    }
  monstersMutex->lock();
  for (std::vector<IMonster *>::iterator it = monsters.begin(); it != monsters.end(); ++it)
    {
      if ((*it)->getType() == 2 && (*it)->getLife() < 5 && status == 1)
	{
	  status = 0;
	  gameTimer -= 1;
	  old.tv_sec = now.tv_sec;
	  old.tv_usec = now.tv_usec;
	  old2.tv_sec = now.tv_sec;
	  old2.tv_usec = now.tv_usec;
	}
      (*it)->update();
      if ((*it)->getX() < -100 || (*it)->getY() < -100 || (*it)->getY() > 600)
	(*it)->setLife(0);
    }
  monstersMutex->unlock();
  playersMutex->lock();
  if (player1)
    player1->update();
  if (player2)
    player2->update();
  if (player3)
    player3->update();
  if (player4)
    player4->update();
  playersMutex->unlock();
  checkCollision();
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

  if (type == RTProtocol::MONSTER_TYPE1)
    external_creator = reinterpret_cast<IMonster *(*)(int, int)>(s->getSharedLibMonsterFirstType()->dlSymb());
  else if (type == RTProtocol::MONSTER_TYPE2)
    external_creator = reinterpret_cast<IMonster *(*)(int, int)>(s->getSharedLibMonsterSecondType()->dlSymb());
  else if (type == RTProtocol::MONSTER_BOSS)
    external_creator = reinterpret_cast<IMonster *(*)(int, int)>(s->getSharedLibMonsterBoss()->dlSymb());
  monstersMutex->lock();
  monsters.push_back(external_creator(100, 100));
  monsters.back()->setId(idMonsters++);
  monstersMutex->unlock();
}

void	Game::deleteMonster(unsigned int id)
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
//AutoMutex am(playersMutex);
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

void		Game::checkCollision()
{
  if (player1 != NULL)
    checkCo(player1);
  if (player2 != NULL)
    checkCo(player2);
  if (player3 != NULL)
    checkCo(player3);
  if (player4 != NULL)
    checkCo(player4);
}

void		Game::checkCo(Player *p)
{
  if (checkCol(p->getX(), p->getY(), 98, 55))
    {
      if (p->getLife() > 0)
	{
	  p->setLife(p->getLife()-1);
	  p->setX(0);
	  p->setY(0);
	}
    }
  if (p != NULL)
    for (unsigned int i = 0; i < p->getFires().size(); ++i)
      {
	if (checkCol(p->getFire(i).x, p->getFire(i).y, 24, 12))
	    p->deleteFire(i);
      }
}

bool		Game::checkCol(int x, int y, int width, int height)
{
  int w, h, fw, fh;

  for (unsigned int i = 0; i < monsters.size(); ++i)
    {
      if (monsters[i]->getType() == RTProtocol::MONSTER_TYPE1)
	{
	  w = 70;
	  h = 70;
	  fw = 24;
	  fh = 12;
	}
      else if (monsters[i]->getType() == RTProtocol::MONSTER_TYPE2)
	{
	  w = 90;
	  h = 64;
	  fw = 24;
	  fh = 12;
	}
      else if (monsters[i]->getType() == RTProtocol::MONSTER_BOSS)
	{
	  w = 214;
	  h = 166;
	  fw = 34;
	  fh = 17;
	}
      if (((monsters[i]->getX() >= x && monsters[i]->getX() <= x+width) ||
	   (monsters[i]->getX()+w >= x && monsters[i]->getX()+w <= x+width)) &&
	  ((monsters[i]->getY() >= y && monsters[i]->getY() <= y+height) ||
	   (monsters[i]->getY()+h >= y && monsters[i]->getY()+h <= y+height)))
	{
	  if (monsters[i]->getLife() > 0)
	    monsters[i]->setLife(monsters[i]->getLife()-1);
	  return true;
	}
      for (unsigned int j = 0; j < monsters[i]->getFires().size(); ++j)
	{
	  if (((monsters[i]->getFire(j).x >= x && monsters[i]->getFire(j).x <= x+width) ||
	       (monsters[i]->getFire(j).x+w >= x && monsters[i]->getFire(j).x+w <= x+width)) &&
	      ((monsters[i]->getFire(j).y >= y && monsters[i]->getFire(j).y <= y+height) ||
	       (monsters[i]->getFire(j).y+h >= y && monsters[i]->getFire(j).y+h <= y+height)))
	    {

	      return true;
	    }
	}
    }
  return false;
}
