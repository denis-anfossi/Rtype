#ifndef		_COMMAND_HPP_
#define		_COMMAND_HPP_

#include "Server.hpp"
#include <cstring>

struct	_command
{
  RTProtocol::Header *h;
  receive	r;
};

class	Server;

class	Command
{
public:
  static void		FindCommand(void *param);
  static Command	*getInstance(void);
  static void		kill(void);

  void	SendConnection(const Player *p, const uint8_t state);
  void	SendGameData(const Player *p);
private:
  void	RecvConnection(const receive& rBody);
  void	RecvConnectionLogIn(const struct sockaddr_in& rcv);
  void	RecvConnectionLogOut(const struct sockaddr_in& rcv);
  void	RecvConnectionCheck(const struct sockaddr_in& rcv);
  void	RecvRunMode(const receive& rBody);
  void	RecvRunModeCreate(const struct sockaddr_in& rcv);
  void	RecvRunModeJoin(const struct sockaddr_in& rcv);
  void	RecvGameAction(const receive& rBody);

  void	SendGameState(const Player *p, const uint8_t state);

  char	*getNewHeader(uint8_t command, int32_t size);

  static Command	*_singleton;

  Command(void);
  ~Command(void);
};

#endif		/* _COMMAND_HPP_ */
