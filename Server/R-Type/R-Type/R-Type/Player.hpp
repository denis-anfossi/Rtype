#ifndef		PLAYER_HPP
#define		PLAYER_HPP

#include	"Receive.hpp"
#include	"Protocol.hpp"
#include	"AutoMutex.hpp"
#include	<vector>

#ifdef __linux__
#include	<sys/time.h>
#else
#include    <sys/timeb.h>
int     gettimeofday(struct timeval *tp, void *tz);
#endif

class Player
{
public:
  Player(const struct sockaddr_in _rcv);
  ~Player(void);

  void	setId(int id);
  void	setId(RTProtocol::Identifier _id);
  void	setIdGame(int _idGame);
  void	setConnect(bool _connect);
  void	setX(int16_t _x);
  void	setY(int16_t _y);
  void	setLife(uint8_t _life);
  void	addFire(void);
  void	deleteFire(unsigned int i);
  const struct sockaddr_in	getSockaddr(void) const;
  RTProtocol::Identifier	getId(void) const;
  int		getIdGame(void) const;
  bool		getConnect(void) const;
  int16_t	getX(void) const;
  int16_t	getY(void) const;
  uint8_t	getLife(void) const;
  std::vector<_fires>	getFires(void) const;
  _fires		getFire(unsigned int j) const;

  void		update(void);
  void		update2(void);

  IMutex	*idMutex;
  IMutex	*idGameMutex;
  IMutex	*connectMutex;
  IMutex	*xMutex;
  IMutex	*yMutex;
  IMutex	*firesMutex;

private:
  const struct sockaddr_in	rcv;
  RTProtocol::Identifier	id;
  int		idGame;
  bool		connect;
  int16_t		x;
  int16_t		y;
  uint8_t		life;
  std::vector<_fires>	fires;
};

#endif		/* PLAYER_HPP */
