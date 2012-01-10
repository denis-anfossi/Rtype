#ifndef		_COMMAND_HPP_
#define		_COMMAND_HPP_

#include "Server.hpp"

class	Server;

class	Command
{
public:
	Command(Server *s);
	~Command(void);

	void	FindCommand(const RTProtocol::Header *h, const receive& rBody);

private:
	void	RecvConnection(const receive& rBody);
	void	RecvConnectionLogIn(const struct sockaddr_in& rcv);
	void	RecvConnectionLogOut(const struct sockaddr_in& rcv);
	void	RecvRunMode(const receive& rBody);
	void	RecvRunModeCreate(const struct sockaddr_in& rcv);
	void	RecvRunModeJoin(const struct sockaddr_in& rcv);
	void	RecvGameAction(const receive& rBody);

	void	SendConnection(const Player *p, const uint8_t state);
	void	SendIdentifier(const Player *p, const uint8_t id);
	void	SendGameState(const Player *p, const uint8_t state);
	void	SendGameAction(const Player *p, );

	void	SendGame();
	void	SendGameNew();
	void	SendGameUpdate();
	void	SendPlayer();
	void	SendPlayerNew();
	void	SendPlayerUpdate();

	char	*getNewHeader(uint8_t command, int32_t size);

	Server	*s;
};

#endif		/* _COMMAND_HPP_ */