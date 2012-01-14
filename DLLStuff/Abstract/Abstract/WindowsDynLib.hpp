#ifndef _WINDOWSDYNLIB_HPP_
#define _WINDOWSDYNLIB_HPP_

#include "IDynLib.hpp"
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdint.h>

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

class WindowsDynLib : public IDynLib
{
private:
  HINSTANCE HandleOpen;
  std::wstring libName;
  std::string SymbolName;
public:
  WindowsDynLib();
  ~WindowsDynLib();
 virtual void* openLib();
  virtual void* dlSymb();
  virtual int closeLib();
  virtual char* errorLib();
  virtual void setlibName(std::string);
  virtual std::wstring getlibName();
  virtual void setSymbolName(std::string);
  virtual std::string getSymbolName();
  virtual void setHandleOpen(void*);
  virtual void* getHandleOpen();
};

#endif