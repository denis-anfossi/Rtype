#include "LinuxDynLib.hpp"

#ifdef __linux__
LinuxDynLib::LinuxDynLib()
{

}

LinuxDynLib::~LinuxDynLib()
{

}

void* LinuxDynLib::openLib()
{
  return dlopen(libName.c_str(), flagOpen);
}

void* LinuxDynLib::dlSymb()
{
  return dlsym(HandleOpen, SymbolName.c_str());
}

int LinuxDynLib::closeLib()
{
  return dlclose(HandleOpen);
}

char* LinuxDynLib::errorLib()
{
  return dlerror();
}

/*int LinuxDynLib::getflagOpen()
{
  return flagOpen;
}
void LinuxDynLib::setflagOpen(int value)
{
  flagOpen = value;
}*/

void* LinuxDynLib::getHandleOpen()
{
  return HandleOpen;
}

void LinuxDynLib::setHandleOpen(void* value)
{
  HandleOpen = value;
}
std::string LinuxDynLib::getlibName()
{
  return libName;
}

void LinuxDynLib::setlibName(std::string value)
{
  libName = value;
}

std::string LinuxDynLib::getSymbolName()
{
  return SymbolName;
}

void LinuxDynLib::setSymbolName(std::string value)
{
  SymbolName = value;
}
#endif