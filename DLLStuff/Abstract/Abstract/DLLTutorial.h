#ifndef _DLL_TUTORIAL_H_
#define _DLL_TUTORIAL_H_
#include <iostream>
#include <stdint.h>

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

class Test
{
public:
	int AddTest(int a, int b)
	{
		return (a+b);
	}
};

class Monster 
{
private:
	uint8_t _X;
	uint8_t _Y;
public:
	Monster(int X, int Y);
	virtual ~Monster();

	virtual uint8_t getX();
	virtual void setX(uint8_t);
	virtual uint8_t getY();
	virtual void setY(uint8_t);
	virtual uint8_t getFire() = 0;
	virtual uint8_t getType() = 0;
	virtual void move() = 0;
};

class MonsterFirstType : public Monster
{
private:
	uint8_t _Type;
	uint8_t _Fire;
public:
	MonsterFirstType(int X, int Y);
	~MonsterFirstType();
	virtual uint8_t getFire();
	virtual uint8_t getType();
	virtual void move();
};

extern "C"
{
   DECLDIR int Add( int a, int b );
   DECLDIR void Function( void );
   DECLDIR void* getInstanceDLL(int X, int Y);
}

#endif