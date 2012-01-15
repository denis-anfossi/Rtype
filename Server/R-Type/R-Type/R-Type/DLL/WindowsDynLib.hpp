#ifndef _WINDOWSDYNLIB_HPP_
#define _WINDOWSDYNLIB_HPP_

#ifndef __linux__

#include "IDynLib.hpp"
#include <cstdio>
#include <cstdint>
#include <iostream>
#define	_WINSOCKAPI_
#include <Windows.h>

class WindowsDynLib : public IDynLib
{
private:
	HMODULE HandleOpen;
	std::string SymbolName;
public:
	WindowsDynLib();
	~WindowsDynLib();
	virtual void* openLib(std::string);
	virtual void* dlSymb();
	virtual int closeLib();
	virtual char* errorLib();
	virtual void setSymbolName(std::string);
};

#endif

#endif
