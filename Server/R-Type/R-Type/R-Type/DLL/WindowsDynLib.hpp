#ifndef _WINDOWSDYNLIB_HPP_
#define _WINDOWSDYNLIB_HPP_

#ifdef WIN32

#include "IDynLib.hpp"
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdint.h>

class Monster 
{
private:
	int16_t _X;
	int16_t _Y;
public:
	Monster(int X, int Y);
	virtual ~Monster();

	
	virtual int16_t getX();
	virtual void setX(int16_t);
	virtual int16_t getY();
	virtual void setY(int16_t);
	virtual uint8_t getFire() = 0;
	virtual uint8_t getType() = 0;
	virtual void move() = 0;
	virtual uint8_t getWidth() = 0;
	virtual uint8_t getHeight() = 0;
};

class MonsterFirstType : public Monster
{
private:
	uint8_t _Type;
	uint8_t _Fire;
	uint8_t _Height;
	uint8_t _Width;
public:
	MonsterFirstType(int X, int Y);
	~MonsterFirstType();
	virtual uint8_t getFire();
	virtual uint8_t getType();
	virtual void move();
	virtual uint8_t getHeight();
	virtual uint8_t getWidth();
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

#endif
