#ifndef _WINDOWSDYNLIB_HPP_
#define _WINDOWSDYNLIB_HPP_

#include "IDynLib.hpp"
#include <stdio.h>
#include <iostream>
#include <Windows.h>

class Test
{
public:
	int AddTest(int a, int b)
	{
		return (a+b);
	}
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