#ifndef _LINUXDYNLIB_HPP_
#define _LINUXDYNLIB_HPP_

#include "IDynLib.hpp"

#ifdef __linux__
#include <dlfcn.h>
#include <cstdio>
#include <iostream>

class LinuxDynLib : public IDynLib
{
private:
  void* HandleOpen;
  std::string SymbolName;
public:
  LinuxDynLib();
  ~LinuxDynLib();
  virtual void* openLib(std::string);
  virtual void* dlSymb();
  virtual int closeLib();
  virtual char* errorLib();
  virtual void setSymbolName(std::string);
};
#endif

#endif
