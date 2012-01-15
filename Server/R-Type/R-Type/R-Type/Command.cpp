#include "Command.hpp"

Command	*Command::_singleton = NULL;

Command	*Command::getInstance(void)
{
	if (_singleton == NULL)
		_singleton = new Command();
	return _singleton;
}

void	Command::kill(void)
{
	if (_singleton != NULL)
	{
		delete	_singleton;
		_singleton = NULL;
	}
}

Command::Command(void)
{ }

Command::~Command(void)
{ }

void	Command::FindCommand(void *param)
{
	std::cout << "FindCommand" << std::endl;

	_command *recv = reinterpret_cast<_command *>(param);
	Command *c = Command::getInstance();

	if (recv->h->Command == RTProtocol::CONNECTION)
		c->RecvConnection(recv->r);
	else if (recv->h->Command == RTProtocol::RUN_MODE)
		c->RecvRunMode(recv->r);
	else if (recv->h->Command == RTProtocol::GAME_ACTION)
		c->RecvGameAction(recv->r);
}

void	Command::RecvConnection(const receive &rBody)
{
  std::cout << "RecvConnection" << std::endl;

  RTProtocol::Connection		*h = reinterpret_cast<RTProtocol::Connection *>(rBody.data_ + sizeof(RTProtocol::Header));
  if (h->StateConnection == RTProtocol::LOG_IN)
    RecvConnectionLogIn(rBody.s_rcv);
  else if (h->StateConnection == RTProtocol::LOG_OUT)
    RecvConnectionLogOut(rBody.s_rcv);
  else if (h->StateConnection == RTProtocol::CHECK)
    RecvConnectionCheck(rBody.s_rcv);
}

void	Command::RecvConnectionLogIn(const struct sockaddr_in& rcv)
{
	std::cout << "RecvConnectionLogIn: " << std::endl;

	Server *s = Server::getInstance();

	if (s->getPlayer(rcv) == 0)
	{
		s->addNewPlayer(rcv);
		SendConnection(s->getPlayer(rcv), RTProtocol::LOG_IN);
	}
}

void	Command::RecvConnectionLogOut(const struct sockaddr_in& rcv)
{
	std::cout << "RecvConnectionLogOut: " << std::endl;

	Server *s = Server::getInstance();

	if (s->getPlayer(rcv) != 0)
	{
		if (s->getPlayer(rcv)->getIdGame() != -1)
		{
			for (int i = 0; i < 4; ++i)
				if (s->getGame(s->getPlayer(rcv))->getPlayer(i) != 0)
					SendConnection(s->getPlayer(rcv), RTProtocol::LOG_OUT);
			s->getGame(s->getPlayer(rcv))->setPlayer(0, s->getPlayer(rcv)->getId());
		}
		SendConnection(s->getPlayer(rcv), RTProtocol::LOG_OUT);
		s->deletePlayer(s->getPlayer(rcv));
	}
}

void	Command::RecvConnectionCheck(const struct sockaddr_in& rcv)
{
	std::cout << "RecvConnectionCheck: " << std::endl;

	Server *s = Server::getInstance();

	s->getPlayer(rcv)->setConnect(true);
}

void	Command::RecvRunMode(const receive& rBody)
{
  std::cout << "RecvRunMode" << std::endl;
  
  RTProtocol::RunMode		*h = reinterpret_cast<RTProtocol::RunMode *>(rBody.data_ + sizeof(RTProtocol::Header));
  if (h->Mode == RTProtocol::CREATE)
	  RecvRunModeCreate(rBody.s_rcv);
  else if (h->Mode == RTProtocol::JOIN)
	  RecvRunModeJoin(rBody.s_rcv);
}

void	Command::RecvRunModeCreate(const struct sockaddr_in& rcv)
{
	std::cout << "RecvRunModeCreate" << std::endl;

	Server *s = Server::getInstance();

	if (s->getPlayer(rcv)->getIdGame() == -1)
	{
		s->addNewGame(s->getPlayer(rcv), s->getAvailableId());
		SendGameState(s->getPlayer(rcv), RTProtocol::START);
	}
}

void	Command::RecvRunModeJoin(const struct sockaddr_in& rcv)
{
	std::cout << "RecvRunModeJoin" << std::endl;

	Server *s = Server::getInstance();

	if (s->getPlayer(rcv)->getIdGame() == -1)
	{
		if (s->getAvailableSlot() != 0)
		{
			s->getPlayer(rcv)->setId(s->getAvailableSlot()->getEmptySlot());
			s->getPlayer(rcv)->setIdGame(s->getAvailableSlot()->getId());
			s->getAvailableSlot()->setPlayer(s->getPlayer(rcv), s->getAvailableSlot()->getEmptySlot());
			SendGameState(s->getPlayer(rcv), RTProtocol::START);
		}
		else
		{
			RecvRunModeCreate(rcv);
		}
	}
}

void	Command::RecvGameAction(const receive& rBody)
{
	std::cout << "RecvGameAction" << std::endl;

	Server *s = Server::getInstance();
	RTProtocol::GameAction	*h = reinterpret_cast<RTProtocol::GameAction *>(rBody.data_ + sizeof(RTProtocol::Header));
//	s->playersMutex->lock();
	s->serverMutex->lock();
	if (s->getPlayer(rBody.s_rcv)->getIdGame() != -1)
	{
	int coord = 0;
	if (h->Action == RTProtocol::UP && isNoUpCollision(rBody.s_rcv) == true)
		s->getPlayer(rBody.s_rcv)->setY((coord = s->getPlayer(rBody.s_rcv)->getY()) - 1);
	else if (h->Action == RTProtocol::DOWN)
		s->getPlayer(rBody.s_rcv)->setY(coord + 1);
	else if (h->Action == RTProtocol::LEFT && (coord = s->getPlayer(rBody.s_rcv)->getX()) >= 0 + 55)
		s->getPlayer(rBody.s_rcv)->setX(coord - 1);
	else if (h->Action == RTProtocol::RIGHT && coord <= 800)
		s->getPlayer(rBody.s_rcv)->setX(coord + 1);
	}
	s->serverMutex->unlock();
//	s->playersMutex->unlock();
}

bool	Command::isNoUpCollision(const struct sockaddr_in& rcv)
{
	Server *s = Server::getInstance();

	int x = s->getPlayer(rcv)->getX();
	int y = s->getPlayer(rcv)->getY();
	for (int i = 0; i < 4; ++i)
	{
		Player *p = s->getGame(s->getPlayer(rcv))->getPlayer(i);
		if (p != s->getPlayer(rcv))
			if ((y + 1) >= (p->getY() - 55) && x <= p->getX() + 98 && x >= p->getX())
				return false;
	}
	return true;
}

bool	Command::isNoDownCollision(const struct sockaddr_in& rcv)
{
	Server *s = Server::getInstance();

	int x = s->getPlayer(rcv)->getX();
	int y = s->getPlayer(rcv)->getY();
	for (int i = 0; i < 4; ++i)
	{
		Player *p = s->getGame(s->getPlayer(rcv))->getPlayer(i);
		if (p != s->getPlayer(rcv))
			if ((y - 1) <= p->getY() && x <= p->getX() + 98 && x >= p->getX())
				return false;
	}
	return true;
}

bool	Command::isNoLeftCollision(const struct sockaddr_in& rcv)
{
	Server *s = Server::getInstance();

	int x = s->getPlayer(rcv)->getX();
	int y = s->getPlayer(rcv)->getY();
	for (int i = 0; i < 4; ++i)
	{
		Player *p = s->getGame(s->getPlayer(rcv))->getPlayer(i);
		if (p != s->getPlayer(rcv))
			if ((x - 1) <= (p->getX() + 98) && y <= p->getY() && y >= p->getY() - 55)
				return false;
	}
	return true;
}

bool	Command::isNoRightCollision(const struct sockaddr_in& rcv)
{
	Server *s = Server::getInstance();

	int x = s->getPlayer(rcv)->getX();
	int y = s->getPlayer(rcv)->getY();
	for (int i = 0; i < 4; ++i)
	{
		Player *p = s->getGame(s->getPlayer(rcv))->getPlayer(i);
		if (p != s->getPlayer(rcv))
			if ((x + 1) >= p->getX() && y <= p->getY() && y >= p->getY() - 55)
				return false;
	}
	return true;
}

void	Command::SendConnection(const Player *p, const uint8_t state)
{
	std::cout << "SendConnection" << std::endl;

	char	*send;

	RTProtocol::Connection c;
	Server *s = Server::getInstance();

	c.StateConnection = state;
	send = getNewHeader(RTProtocol::CONNECTION, sizeof(RTProtocol::Header) + sizeof(RTProtocol::Connection));
	std::memcpy(send + sizeof(RTProtocol::Header), &c, sizeof(RTProtocol::Connection));
	s->getSocket()->SendData(p->getSockaddr().sin_addr, p->getSockaddr().sin_port, send, sizeof(RTProtocol::Header) + sizeof(RTProtocol::Connection), 0);
}

void	Command::SendGameState(const Player *p, const uint8_t state)
{
	std::cout << "SendGameState" << std::endl;

	char	*send;
	RTProtocol::GameState g;
	Server *s = Server::getInstance();

	g.State = state;
	send = getNewHeader(RTProtocol::GAME_STATE, sizeof(RTProtocol::Header) + sizeof(RTProtocol::GameState));
	std::memcpy(send + sizeof(RTProtocol::Header), &g, sizeof(RTProtocol::GameState));
	s->getSocket()->SendData(p->getSockaddr().sin_addr, p->getSockaddr().sin_port, send, sizeof(RTProtocol::Header) + sizeof(RTProtocol::GameState), 0);
}

void	Command::SendGameData(const Player *p)
{
//	std::cout << "SendGameData" << std::endl;

	char	*send;
	RTProtocol::GameData data;
	Server *s = Server::getInstance();

	int len = 0;
	for (int i = 0; i < 4; ++i)
		if (s->getGame(p)->getPlayer(i) != 0)
			len += sizeof(RTProtocol::GameData);
	for (unsigned int i = 0; i < s->getGame(p)->getMonsters().size(); ++i)
		len += sizeof(RTProtocol::GameData);
	send = getNewHeader(RTProtocol::GAME_DATA, sizeof(RTProtocol::Header) + len);
	len = sizeof(RTProtocol::Header);
	for (int i = 0; i < 4; ++i)
		if (s->getGame(p)->getPlayer(i) != 0)
		{
			data.ExternType = RTProtocol::PLAYER;
			data.InternType = s->getGame(p)->getPlayer(i)->getId().Id;
			data.Id = s->getGame(p)->getPlayer(i)->getId().Id;
			data.x = s->getGame(p)->getPlayer(i)->getX();
			data.y = s->getGame(p)->getPlayer(i)->getY();
			std::memcpy(send + len, &data, sizeof(RTProtocol::GameData));
			len += sizeof(RTProtocol::GameData);
		}
	for (unsigned int i = 0; i < s->getGame(p)->getMonsters().size(); ++i)
	{
		data.ExternType = RTProtocol::MONSTER;
		data.InternType = s->getGame(p)->getMonster(i)->getType();
		data.Id = i;
		data.x = s->getGame(p)->getMonster(i)->getX();
		data.y = s->getGame(p)->getMonster(i)->getY();
		std::memcpy(send + len, &data, sizeof(RTProtocol::GameData));
		len += sizeof(RTProtocol::GameData);
	}
	s->getSocket()->SendData(p->getSockaddr().sin_addr, p->getSockaddr().sin_port, send, len, 0);
}

char	*Command::getNewHeader(uint8_t command, int32_t size)
{
//	std::cout << "getNewHeader" << std::endl;

	RTProtocol::Header	h;

	h.Command = command;
	h.Size = size;

	char *header = new char[size];
	std::memcpy(header, &h, sizeof(RTProtocol::Header));

	return (header);
}
