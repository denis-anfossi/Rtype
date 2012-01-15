#ifndef _WINDOWSDYNLIB_HPP_
#define _WINDOWSDYNLIB_HPP_

#ifdef WIN32

#include "IDynLib.hpp"
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdint.h>

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
