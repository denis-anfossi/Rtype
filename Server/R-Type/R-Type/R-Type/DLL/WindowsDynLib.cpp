#include "WindowsDynLib.hpp"

#ifndef __linux__

#include <Windows.h>

WindowsDynLib::WindowsDynLib()
{}

WindowsDynLib::~WindowsDynLib()
{}

void *WindowsDynLib::openLib(std::string libName)
{
	HandleOpen = LoadLibrary(libName.c_str());

	return HandleOpen;
}

void* WindowsDynLib::dlSymb()
{
	return GetProcAddress(HandleOpen, SymbolName.c_str());
}

int WindowsDynLib::closeLib()
{
	return FreeLibrary(HandleOpen);
}

char* WindowsDynLib::errorLib()
{
	return 0;
}

void WindowsDynLib::setSymbolName(std::string sym)
{
	SymbolName = sym.c_str();
}

#endif
