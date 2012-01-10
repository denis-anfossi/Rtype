#ifndef		SERVER_HPP
#define		SERVER_HPP

#ifdef	__linux__
#include	"Socket/UnixSocket.hpp"
#else
#include	"Socket\WinSocket.hpp"
#endif

#include	"Game.hpp"
#include	"Player.hpp"
#include	"Protocol.hpp"
#include	"Command.hpp"

#include	<vector>

class	Command;

class	Server
{
public:
	Server(void);
	~Server(void);

	void	init(void);
	void	running(void);

	void	addNewPlayer(const struct sockaddr_in rcv);
	void	addNewGame(void);
	Player	*getPlayer(const struct sockaddr_in rcv) const;
	Game	*getGame(void) const;
	Game	*getGame(const Player *p) const;
	Game	*getAvailableSlot(void) const;
	ISocket	*getSocket(void) const;
	void	deletePlayer(const Player *p);
	void	deleteGame(const Game *g);

private:
	ISocket		*socket;
	std::vector<Player *>	players;
	std::vector<Game *>		games;
};

#endif		/* SERVER_HPP */
