#ifdef __linux__
#include "LinuxDynLib.hpp"

std::wstring StringToWString(const std::string& s)
{
  std::wstring temp(s.length(),L' ');
  std::copy(s.begin(), s.end(), temp.begin());
  return temp;
}

std::string WStringToString(const std::wstring& s)
{
  std::string temp(s.length(), ' ');
  std::copy(s.begin(), s.end(), temp.begin());
  return temp;
}

LinuxDynLib::LinuxDynLib()
{}

LinuxDynLib::~LinuxDynLib()
{}

void* LinuxDynLib::openLib()
{
  return dlopen(WStringToString(libName).c_str(), RTLD_LAZY);
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

void* LinuxDynLib::getHandleOpen()
{
  return HandleOpen;
}

void LinuxDynLib::setHandleOpen(void* value)
{
  HandleOpen = value;
}

std::wstring LinuxDynLib::getlibName()
{
  return libName;
}

void LinuxDynLib::setlibName(std::string value)
{
  libName = StringToWString(value);
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
