#include	"Server.hpp"

Server	*Server::_singleton = NULL;

Server	*Server::getInstance()
{
	if (_singleton == NULL)
		_singleton = new Server();
	return _singleton;
}

void	Server::kill()
{
	if (_singleton != NULL)
	{
		delete	_singleton;
		_singleton = NULL;
	}
}

Server::Server(void)
{
#ifdef __linux__
	serverMutex = new UnixMutex();
	playersMutex = new UnixMutex();
#else
	serverMutex = new WinMutex();
	playersMutex = new WinMutex();
#endif
	serverMutex->init();
	playersMutex->init();

	serverMutex->lock();
	threadPool = ThreadPool_::getInstance();
	ThreadPool_::_singletonMutex->init();
	serverMutex->unlock();
#ifdef	__linux__
	socket = new UnixSocket();
#else
	socket = new WinSocket();
#endif
}

Server::~Server(void)
{
	for (std::vector<Player *>::const_iterator it = players.begin(); it != players.end(); ++it)
		delete *it;
	for (std::vector<Game *>::const_iterator it = games.begin(); it != games.end(); ++it)
		delete *it;
	delete socket;
	serverMutex->lock();
	ThreadPool_::kill();
	serverMutex->unlock();
	delete serverMutex;
}

void	Server::init(void)
{
	threadPool->ThreadPoolInit(10);
	if (!(socket->CreateSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
		throw std::exception();
	if (!(socket->BindSocket(AF_INET, 4242)))
		throw std::exception();
}

void	Server::running(void)
{
	RTProtocol::Header		*h;
	Command		*c = Command::getInstance();

	threadPool->QueuePush(Server::checkConnectionClients, NULL);
	threadPool->QueuePush(Server::sendUpdateClients, NULL);
	while (1)
	{
		receive rHeader = socket->RecvData(sizeof(RTProtocol::Header), MSG_PEEK);
		h = reinterpret_cast<RTProtocol::Header *>(rHeader.data_);
		receive rBody = socket->RecvData(h->Size, 0);
		_command	*recv = new _command();
		recv->h = h;
		recv->r = rBody;
		threadPool->QueuePush(Command::FindCommand, recv);
	}
}

#ifdef __linux__
	#infclude <unistd.h>
#endif

void	Server::checkConnectionClients(void *param)
{
	Command *c = Command::getInstance();
	Server	*s = Server::getInstance();

	while (1)
	{
		for (unsigned int i = 0; i < s->getPlayers().size(); ++i)
		{
			if (s->getPlayer(i)->getConnect() == true)
			{
				s->getPlayer(i)->setConnect(false);
				c->SendConnection(s->getPlayer(i), RTProtocol::CHECK);
			}
			else if (s->getPlayer(i)->getIdGame() != -1)
			{
				for (int j = 0; j < 4; ++j)
					if (s->getGame(s->getPlayer(i))->getPlayer(i) != 0)
						c->SendConnection(s->getPlayer(i), RTProtocol::LOG_OUT);
				s->getGame(s->getPlayer(i))->setPlayer(0, s->getPlayer(i)->getId());
			}
			s->deletePlayer(s->getPlayer(i));
		}
#ifdef __linux__
		sleep(30);
#else
		Sleep(30000);
#endif
	}
}

void	Server::sendUpdateClients(void *param)
{
	struct timeval	now;
	struct timeval	diff;

	Command *c = Command::getInstance();
	Server	*s = Server::getInstance();

	while (1)
	{
		gettimeofday(&now, NULL);
		for (unsigned int i = 0; i < s->getPlayers().size(); ++i)
		{
			if (s->getPlayer(i)->getIdGame() != -1)
				c->SendGameData(s->getPlayer(i));
		}
		Sleep(10);
		gettimeofday(&diff, NULL);
		diff.tv_sec = diff.tv_sec - now.tv_sec;
		if (diff.tv_sec > 0)
		{
			diff.tv_usec += diff.tv_sec * 1000000;
			diff.tv_sec = 0;
		}
		diff.tv_usec = (1000000 - (diff.tv_usec - now.tv_usec) ) / 120;
#ifdef __linux__
		usleep(diff.tv_usec);
#else
		Sleep(diff.tv_usec / 1000);
#endif
	}
}

void	Server::addNewPlayer(const struct sockaddr_in rcv)
{
	playersMutex->lock();
	if (getPlayer(rcv) == 0)
		players.push_back(new Player(rcv));
	playersMutex->unlock();
}

Player	*Server::getPlayer(const struct sockaddr_in rcv) const
{
  for (std::vector<Player *>::const_iterator it = players.begin(); it != players.end(); ++it)
    {
      Player *p = *it;
      uint32_t u = p->getSockaddr().sin_addr.s_addr;
      if (p->getSockaddr().sin_addr.s_addr == rcv.sin_addr.s_addr && p->getSockaddr().sin_port == rcv.sin_port)
		return p;
    }
  return 0;
}

Player	*Server::getPlayer(const unsigned int it) const
{
	if (players.size() > it)
		return players[it];
	return NULL;
}

std::vector<Player *>	Server::getPlayers(void) const
{
	return players;
}

void	Server::deletePlayer(const Player *p)
{
	for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
		if (p == *it)
		{
			players.erase(it);
			break;
		}
}

void	Server::addNewGame(Player *p, int id)
{
	games.push_back(new Game(p, id));
	playersMutex->lock();
	p->setIdGame(id);
	playersMutex->unlock();
}

Game	*Server::getGame(void) const
{
	return games.back();
}

Game	*Server::getGame(const Player *p) const
{
	for (std::vector<Game *>::const_iterator it = games.begin(); it != games.end(); ++it)
		if ((*it)->getId() == p->getIdGame())
			return ((*it));
	return 0;
}

std::vector<Game *>		Server::getGames(void) const
{
	return games;
}

void	Server::deleteGame(const Game *g)
{
	for (std::vector<Game *>::iterator it = games.begin(); it != games.end(); ++it)
		if (g == *it)
		{
			games.erase(it);
			break;
		}
}

int		Server::getAvailableId(void) const
{
	int	id = 0;

	for (std::vector<Game *>::const_iterator it = games.begin(); it != games.end(); ++it)
		if ((*it)->getId() >= id)
			++id;
	return id;
}

Game	*Server::getAvailableSlot(void) const
{
	for (std::vector<Game *>::const_iterator it = games.begin(); it != games.end(); ++it)
		if ((*it)->getEmptySlot() != -1)
			return (*it);
	return 0;
}

ISocket	*Server::getSocket(void) const
{
	return socket;
}

#ifndef	__linux__

int		gettimeofday (struct timeval *tp, void *tz)
{
  struct _timeb timebuffer;
  _ftime_s(&timebuffer);
  tp->tv_sec = timebuffer.time;
  tp->tv_usec = timebuffer.millitm * 1000;
  return 0;
}

#endif