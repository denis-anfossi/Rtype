#include "Player.hpp"

Player::Player(const struct sockaddr_in _rcv): rcv(_rcv), idGame(-1), connect(true), x(0), y(0)
{
	id.Id = RTProtocol::NO_PLAY;

#ifdef __linux__
	idMutex = new UnixMutex();
	idGameMutex = new UnixMutex();
	connectMutex = new UnixMutex();
	xMutex = new UnixMutex();
	yMutex = new UnixMutex();
#else
	idMutex = new WinMutex();
	idGameMutex = new WinMutex();
	connectMutex = new WinMutex();
	xMutex = new WinMutex();
	yMutex = new WinMutex();
#endif

	idMutex->init();
	idGameMutex->init();
	connectMutex->init();
	xMutex->init();
	yMutex->init();
}

Player::~Player(void)
{ 
	idMutex->destroy();
	idGameMutex->destroy();
	connectMutex->destroy();
	xMutex->destroy();
	yMutex->destroy();

	delete	idMutex;
	delete	idGameMutex;
	delete	connectMutex;
	delete	xMutex;
	delete	yMutex;
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
