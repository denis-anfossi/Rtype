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

	if (s->getPlayer(rcv) != 0)
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
		std::cout << "SEND GAME STATE" << std::endl;
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
	Server *s = Server::getInstance();
	RTProtocol::GameAction	*h = reinterpret_cast<RTProtocol::GameAction *>(rBody.data_ + sizeof(RTProtocol::Header));
	s->playersMutex->lock();
	if (s->getPlayer(rBody.s_rcv)->getIdGame() != -1)
	{
		if (h->Action == RTProtocol::UP && s->getPlayer(rBody.s_rcv)->getY() > 0)
			s->getPlayer(rBody.s_rcv)->setY(s->getPlayer(rBody.s_rcv)->getY() - 15);
		else if (h->Action == RTProtocol::DOWN && s->getPlayer(rBody.s_rcv)->getY() <= 530)
			s->getPlayer(rBody.s_rcv)->setY(s->getPlayer(rBody.s_rcv)->getY() + 15);
		else if (h->Action == RTProtocol::LEFT && (s->getPlayer(rBody.s_rcv)->getX()) > 0)
			s->getPlayer(rBody.s_rcv)->setX(s->getPlayer(rBody.s_rcv)->getX() - 15);
		else if (h->Action == RTProtocol::RIGHT && s->getPlayer(rBody.s_rcv)->getX() <= 692)
			s->getPlayer(rBody.s_rcv)->setX(s->getPlayer(rBody.s_rcv)->getX() + 15);
	}
	s->playersMutex->unlock();
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
	char	*send;
	RTProtocol::GameData data;
	Server *s = Server::getInstance();

	int len = 0;
	for (int i = 0; i < 4; ++i)
		if (s->getGame(p)->getPlayer(i) != 0)
			len += sizeof(RTProtocol::GameData);
	for (unsigned int i = 0; i < s->getGame(p)->getMonsters().size(); ++i)
		len += sizeof(RTProtocol::GameData);
/* C"EST EN DUR !!!*/
len += sizeof(RTProtocol::GameData);
len += sizeof(RTProtocol::GameData);
static int iii = 0;
	if (iii++ == 300)
		len += sizeof(RTProtocol::GameData);
/* C"EST EN DUR !!!*/
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
			data.alive = 1;
			std::memcpy(send + len, &data, sizeof(RTProtocol::GameData));
			len += sizeof(RTProtocol::GameData);
		}
	for (unsigned int i = 0; i < s->getGame(p)->getMonsters().size(); ++i)
	{
 		data.ExternType = RTProtocol::MONSTER;
//		data.InternType = s->getGame(p)->getMonster(i)->getType();
//		data.Id = s->getGame(p)->getMonster(i)->getId();
/* C"EST EN DUR !!!*/
		data.InternType = RTProtocol::MONSTER_TYPE1;
		data.Id = 10;
/* C"EST EN DUR !!!*/
		data.x = s->getGame(p)->getMonster(i)->getX();
		data.y = s->getGame(p)->getMonster(i)->getY();
		data.alive = 1;
		std::memcpy(send + len, &data, sizeof(RTProtocol::GameData));
		len += sizeof(RTProtocol::GameData);
	}
		data.ExternType = RTProtocol::FIRE;
		data.InternType = RTProtocol::FIRE_PLAYER;
		data.Id = 0;
		data.x = 50;
		data.y = 50;
		data.alive = 1;
		std::memcpy(send + len, &data, sizeof(RTProtocol::GameData));
		len += sizeof(RTProtocol::GameData);
		data.ExternType = RTProtocol::FIRE;
		data.InternType = RTProtocol::FIRE_MONSTER;
		data.Id = 1;
		data.x = 55;
		data.y = 55;
		data.alive = 1;
		std::memcpy(send + len, &data, sizeof(RTProtocol::GameData));
		len += sizeof(RTProtocol::GameData);
	static int ii = 0;
		if (ii++ == 300)
		{
		std::cout << "MORT" << std::endl;
		data.ExternType = RTProtocol::MONSTER;
		data.InternType = RTProtocol::MONSTER_TYPE2;
		data.Id = 1;
		data.x = 50;
		data.y = 300;
		data.alive = 0;
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
