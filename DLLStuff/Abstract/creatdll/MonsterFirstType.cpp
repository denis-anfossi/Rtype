#include "Monster.h"

MonsterFirstType::MonsterFirstType(int X, int Y)
	: Monster(X, Y)
{
	_Type = 0;
	_Fire = 0;
}

MonsterFirstType::~MonsterFirstType()
{}

uint8_t MonsterFirstType::getType()
{
	return _Type;
}

uint8_t MonsterFirstType::getFire()
{
	return _Fire;
}

void MonsterFirstType::move()
{
	setX(100);
	setY(100);
}