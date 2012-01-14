#ifndef _LINUXDYNLIB_HPP_
#define _LINUXDYNLIB_HPP_

#ifdef __linux__
#include "IDynLib.hpp"
#include <dlfcn.h>
#include <stdio.h>
#include <iostream>

class LinuxDynLib : public IDynLib
{
private:
  void* HandleOpen;
  std::wstring libName;
  std::string SymbolName;
public:
  LinuxDynLib();
  ~LinuxDynLib();
  virtual void* openLib();
  virtual void* dlSymb();
  virtual int closeLib();
  virtual char* errorLib();
  void* getHandleOpen();
  void setHandleOpen(void*);
  std::wstring getlibName();
  void setlibName(std::string);
  std::string getSymbolName();
  void setSymbolName(std::string);
};
#endif

#endif
