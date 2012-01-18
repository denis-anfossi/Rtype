#ifndef		MONSTER_SECOND_TYPE_HPP
#define		MONSTER_SECOND_TYPE_HPP

#include	"IMonster.hpp"
#include	<time.h>
#include	<iostream>

class MonsterSecondType	: public IMonster
{
public:
	MonsterSecondType(int, int);
	~MonsterSecondType(void);

	virtual int16_t					getX(void);
	virtual int16_t					getY(void);
	virtual	std::vector<int16_t>	getXFires(void);
	virtual	std::vector<int16_t>	getYFires(void);
	virtual uint8_t					getType(void);
	virtual void					update(void);
	virtual uint8_t					getWidth(void);
	virtual uint8_t					getHeight(void);
	virtual uint8_t					getLife(void);
	virtual void					setLife(uint8_t);
	virtual	uint32_t				getId(void);
	virtual void					setId(uint32_t id);
	virtual void					ActFire();
	virtual void					UpdateFire();
private:
	uint32_t	id;
	uint8_t		width;
	uint8_t		height;
	uint8_t		type;
	uint8_t		fire;
	int16_t		x;
	int16_t		y;
	uint8_t		life;
	uint8_t		modefire;
	std::vector<int16_t>	xFires;
	std::vector<int16_t>	yFires;
};

#endif	/* MONSTER_SECOND_TYPE_HPP */
