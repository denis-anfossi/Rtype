#include "Monster.h"

MonsterFirstType::MonsterFirstType(int X, int Y)
	: Monster(X, Y)
{
	_Type = 0;
	_Fire = 0;
	_Height = 0;
	_Width = 0;
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

uint8_t MonsterFirstType::getHeight()
{
	return _Height;
}

uint8_t MonsterFirstType::getWidth()
{
	return _Width;
}

void MonsterFirstType::move()
{
	setX(100);
	setY(100);
}