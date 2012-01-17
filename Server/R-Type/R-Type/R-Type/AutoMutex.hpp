#ifndef		AUTO_MUTEX_HPP
#define		AUTO_MUTEX_HPP

#ifdef __linux__
#include	"Thread/UnixMutex.hpp"
#else
#include	"Thread\WinMutex.hpp"
#endif

class AutoMutex
{
public:
	AutoMutex(IMutex *_mutex);
	~AutoMutex(void);

private:
	IMutex	*mutex;
};

#endif
