#include "Player.hpp"

Player::Player(const struct sockaddr_in _rcv): rcv(_rcv), idGame(-1), connect(true), x(0), y(0), life(15)
{
  id.Id = RTProtocol::NO_PLAY;

#ifdef __linux__
  idMutex = new UnixMutex();
  idGameMutex = new UnixMutex();
  connectMutex = new UnixMutex();
  xMutex = new UnixMutex();
  yMutex = new UnixMutex();
  firesMutex = new UnixMutex();
#else
  idMutex = new WinMutex();
  idGameMutex = new WinMutex();
  connectMutex = new WinMutex();
  xMutex = new WinMutex();
  yMutex = new WinMutex();
  firesMutex = new WinMutex();
#endif

  idMutex->init();
  idGameMutex->init();
  connectMutex->init();
  xMutex->init();
  yMutex->init();
  firesMutex->init();
}

Player::~Player(void)
{ 
  idMutex->destroy();
  idGameMutex->destroy();
  connectMutex->destroy();
  xMutex->destroy();
  yMutex->destroy();
  firesMutex->destroy();

  delete	idMutex;
  delete	idGameMutex;
  delete	connectMutex;
  delete	xMutex;
  delete	yMutex;
  delete	firesMutex;
}

void	Player::setId(int _id)
{
  AutoMutex	am(idMutex);
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
  AutoMutex	am(idMutex);
  id = _id;
}

const struct sockaddr_in	Player::getSockaddr(void) const
{
  return rcv;
}

RTProtocol::Identifier	Player::getId() const
{
  AutoMutex	am(idMutex);
  return id;
}

void	Player::setIdGame(int _idGame)
{
  AutoMutex	am(idGameMutex);
  idGame = _idGame;
}

int		Player::getIdGame(void) const
{
  AutoMutex	am(idGameMutex);
  return idGame;
}

void	Player::setConnect(bool _connect)
{
  AutoMutex	am(connectMutex);
  connect = _connect;
}

bool	Player::getConnect(void) const
{
  AutoMutex	am(connectMutex);
  return connect;
}

void	Player::setX(int16_t _x)
{
  AutoMutex	am(xMutex);
  x = _x;
}

int16_t	Player::getX(void) const
{
  AutoMutex	am(xMutex);
  return x;
}

void	Player::setY(int16_t _y)
{
  AutoMutex	am(yMutex);
  y = _y;
}

int16_t	Player::getY(void) const
{
  AutoMutex	am(yMutex);
  return y;
}

void	Player::setLife(uint8_t	_life)
{
  life = _life;
}

uint8_t	Player::getLife(void) const
{
  return life;
}

void	Player::addFire(void)
{
  struct timeval	now;
  _fires		fire;
  fire.x = x + 97;
  fire.y = y + 27;
  gettimeofday(&now, NULL);
  fire.id = ((now.tv_sec % 10000) * 100000) + (now.tv_usec % 100000);
  fire.alive = 1;
  AutoMutex	am(firesMutex);
  fires.push_back(fire);
}

void	Player::deleteFire(unsigned int i)
{
  if (i < fires.size())
    {
      if (fires[i].alive > 0)
	fires[i].alive = 0;
      else
	fires.erase(fires.begin()+i);
    }
}

std::vector<_fires>	Player::getFires(void) const
{
  AutoMutex	am(firesMutex);
  return fires;
}

_fires			Player::getFire(unsigned int j) const
{
  AutoMutex	am(firesMutex);
  return fires[j];
}

void		Player::update(void)
{
  AutoMutex	am(firesMutex);
  for (unsigned int i = 0; i < fires.size(); ++i)
    {
      fires[i].x += 4;
      if (fires[i].x > 805 && fires[i].alive == 1)
	fires[i].alive = 0;
    }
}

void		Player::update2(void)
{
  AutoMutex	am(firesMutex);
  for (unsigned int i = 0; i < fires.size(); ++i)
    {
      if (fires[i].alive == 0)
	deleteFire(i);
    }
}
