#ifndef		SERVER_HPP
#define		SERVER_HPP

#ifdef __linux__
#include	"DLL/LinuxDynLib.hpp"
#else
#include	"DLL\WindowsDynLib.hpp"
#endif
#ifdef	__linux__
#include	"Socket/UnixSocket.hpp"
#include	<sys/time.h>
#else
#include	"Socket\WinSocket.hpp"
#endif

#include	"ThreadPool_.hpp"
#include	"Game.hpp"
#include	"Player.hpp"
#include	"Protocol.hpp"
#include	"Command.hpp"

#include	<stdexcept>
#include	<vector>

class	Command;
class	Game;

class	Server
{
public:
	void	init(void);
	void	running(void);

	void	addNewPlayer(const struct sockaddr_in rcv);
	void	addNewGame(Player *p, int id);
	IDynLib	*getSharedLibMonsterFirstType(void) const;
	IDynLib	*getSharedLibMonsterSecondType(void) const;
	Player	*getPlayer(const struct sockaddr_in rcv) const;
	Player	*getPlayer(const unsigned int it) const;
	std::vector<Player *>	getPlayers(void) const;
	Game	*getGame(void) const;
	Game	*getGame(const Player *p) const;
	std::vector<Game *>		getGames(void) const;
	int		getAvailableId(void) const;
	Game	*getAvailableSlot(void) const;
	ISocket	*getSocket(void) const;
	void	deletePlayer(const Player *p);
	void	deleteGame(const Game *g);

	static void		checkConnectionClients(void *param);
	static void		sendUpdateClients(void *param);

	static Server	*getInstance(void);
	static void		kill(void);

	IMutex		*threadPoolMutex;
	IMutex		*socketMutex;
	IMutex		*sharedMonsterFirstTypeMutex;
	IMutex		*sharedMonsterSecondTypeMutex;
	IMutex		*playersMutex;
	IMutex		*gamesMutex;
private:
	Server(void);
	~Server(void);

	static Server	*_singleton;

	ThreadPool_	*threadPool;
	ISocket		*socket;
	IDynLib		*sharedLibMonsterFirstType;
	IDynLib		*sharedLibMonsterSecondType;
	std::vector<Player *>	players;
	std::vector<Game *>		games;
};

#ifndef __linux__
#include	<sys/timeb.h>
int	gettimeofday(struct timeval *tp, void *tz);
#endif

#endif		/* SERVER_HPP */
