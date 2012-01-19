#ifndef		PLAYER_HPP
#define		PLAYER_HPP

#include	"Receive.hpp"
#include	"Protocol.hpp"
#include	"AutoMutex.hpp"
#include	<vector>

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
	void	addFire(void);
	void	deleteFire(int16_t _x, int16_t _y);
	const struct sockaddr_in	getSockaddr(void) const;
	RTProtocol::Identifier	getId(void) const;
	int		getIdGame(void) const;
	bool	getConnect(void) const;
	int16_t	getX(void) const;
	int16_t	getY(void) const;
	std::vector<int16_t>	getXFires(void) const;
	std::vector<int16_t>	getYFires(void) const;

	IMutex	*idMutex;
	IMutex	*idGameMutex;
	IMutex	*connectMutex;
	IMutex	*xMutex;
	IMutex	*yMutex;
	IMutex	*xFiresMutex;
	IMutex	*yFiresMutex;

	int		alive;
private:
	const struct sockaddr_in		rcv;
	RTProtocol::Identifier	id;
	int			idGame;
	bool		connect;
	int16_t		x;
	int16_t		y;
	std::vector<int16_t>		xFires;
	std::vector<int16_t>		yFires;

};

#endif		/* PLAYER_HPP */
