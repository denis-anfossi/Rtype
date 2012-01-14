#include "Monster.h"

Monster::Monster(int X, int Y)
{
	_X = X;
	_Y = Y;
}

Monster::~Monster()
{}

uint8_t Monster::getX()
{
	return _X;
}

void Monster::setX(uint8_t X)
{
	_X = X;
}

uint8_t Monster::getY()
{
	return _Y;
}

void Monster::setY(uint8_t Y)
{
	_Y = Y;
}