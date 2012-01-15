#ifndef _IDYNLIB_HPP_
#define _IDYNLIB_HPP_
#include <iostream>
class IDynLib
{
public:
  virtual ~IDynLib(){};
  virtual void* openLib() = 0;
  virtual void* dlSymb() = 0;
  virtual int closeLib() = 0;
  virtual char* errorLib() = 0;
  virtual void setlibName(std::string) = 0;
  virtual std::wstring getlibName() = 0;
  virtual void setSymbolName(std::string) = 0;
  virtual std::string getSymbolName() = 0;
  virtual void setHandleOpen(void*) = 0;
  virtual void* getHandleOpen() = 0;
};

#endif