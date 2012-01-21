#include "LinuxDynLib.hpp"

#ifdef __linux__

LinuxDynLib::LinuxDynLib()
{}

LinuxDynLib::~LinuxDynLib()
{}

void* LinuxDynLib::openLib(std::string libName)
{
  HandleOpen = dlopen(libName.c_str(), RTLD_LAZY);
  return HandleOpen;
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

void LinuxDynLib::setSymbolName(std::string value)
{
  SymbolName = value;
}

#endif
