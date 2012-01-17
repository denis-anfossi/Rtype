#include "AutoMutex.hpp"

AutoMutex::AutoMutex(IMutex *_mutex): mutex(_mutex)
{
	mutex->lock();
}

AutoMutex::~AutoMutex(void)
{
	mutex->unlock();
}
