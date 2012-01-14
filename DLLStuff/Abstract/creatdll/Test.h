#ifndef _TEST_H_
#define _TEST_H_

class Monster
{
private:
	uint8_t _Type;
	uint8_t _X;
	uint8_t _Y;
	uint8_t _Fire;
public:
	Monster();
	~Monster();
	uint8_t getType();
	void setType(uint8_t);
	uint8_t getX();
	void setX(uint8_t);
	uint8_t getY();
	void setY(uint8_t);
	uint8_t getFire();
	void setFire(uint8_t);
};

#endif