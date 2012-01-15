#ifndef		MONSTER_FIRST_TYPE_HPP
#define		MONSTER_FIRST_TYPE_HPP

#include	"IMonster.hpp"

class MonsterFirstType	: public IMonster
{
public:
	MonsterFirstType(int, int);
	~MonsterFirstType(void);

	virtual int16_t					getX(void);
	virtual int16_t					getY(void);
	virtual	std::vector<int16_t>	getXFires(void);
	virtual	std::vector<int16_t>	getYFires(void);
	virtual uint8_t					getType(void);
	virtual uint8_t					getWidth(void);
	virtual uint8_t					getHeight(void);
	virtual void					update(void);

private:
	uint8_t		width;
	uint8_t		height;
	uint8_t		type;
	uint8_t		fire;
	int16_t		x;
	int16_t		y;
	std::vector<int16_t>	xFires;
	std::vector<int16_t>	yFires;
};

#endif	/* MONSTER_FIRST_TYPE_HPP */