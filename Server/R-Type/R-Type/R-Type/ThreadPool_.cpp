#include "ThreadPool_.hpp"
#include <iostream>

ThreadPool_	*ThreadPool_::_singleton = NULL;
/*
#ifdef __linux__
IMutex *ThreadPool_::_singletonMutex = new UnixMutex();
#else
IMutex *ThreadPool_::_singletonMutex = new WinMutex();
#endif
*/
ThreadPool_	*ThreadPool_::getInstance()
{
  if (_singleton == NULL)
    _singleton = new ThreadPool_();
  return _singleton;
}

void	ThreadPool_::kill()
{
  if (_singleton != NULL)
    {
      delete	_singleton;
      _singleton = NULL;
    }
}

ThreadPool_::ThreadPool_(void)
{ }

ThreadPool_::~ThreadPool_(void)
{ }

bool	ThreadPool_::ThreadPoolInit(int nbThreads)
{
	Terminated = false;
#ifdef __linux__
	ThreadQueueMutex = new UnixMutex();
	TaskQueueMutex = new UnixMutex();
	TerminatedMutex = new UnixMutex();
	for (int i = 0; i < nbThreads; ++i)
		ThreadQueue.push_back(new UnixThread());
#else
	ThreadQueueMutex = new WinMutex();
	TaskQueueMutex = new WinMutex();
	TerminatedMutex = new WinMutex();
	for (int i = 0; i < nbThreads; ++i)
		ThreadQueue.push_back(new WinThread());
#endif

	ThreadQueueMutex->init();
	TaskQueueMutex->init();
	TerminatedMutex->init();
	for (int i = 0; i < nbThreads; ++i)
		ThreadQueue[i]->create(ThreadPoolRoutine, NULL);
	return true;
}

void	ThreadPool_::ThreadPoolDestroy()
{
	TerminatedMutex->lock();
	Terminated = true;
	TerminatedMutex->unlock();
	for (unsigned int i = 0; i < ThreadQueue.size(); ++i)
		ThreadQueue[i]->join();
	ThreadQueueMutex->lock();
	for (unsigned int i = 0; i < ThreadQueue.size(); ++i)
		delete ThreadQueue[i];
	ThreadQueueMutex->unlock();
	ThreadQueueMutex->destroy();
	TaskQueueMutex->destroy();
	TerminatedMutex->destroy();
	delete ThreadQueueMutex;
	delete TaskQueueMutex;
	delete TerminatedMutex;
}

void	ThreadPool_::TaskExec(Task *task)
{
	AutoMutex	am(TaskQueueMutex);
	task->function(task->data);
}

bool	ThreadPool_::ThreadPush()
{
	AutoMutex	am(ThreadQueueMutex);
	return true;
}

bool	ThreadPool_::ThreadPop()
{
	AutoMutex	am(ThreadQueueMutex);
	return true;
}

void	ThreadPool_::QueuePush(void (*function)(void *), void *param)
{
	Task *task = new Task();
	task->function = function;
	task->data = param;
	AutoMutex	am(TaskQueueMutex);
//	TaskQueueMutex->lock();
	TaskQueue.push_back(task);
//	TaskQueueMutex->unlock();
}

Task	*ThreadPool_::QueuePop(Task *task)
{
	TaskQueueMutex->lock();
//	AutoMutex	am(TaskQueueMutex);
	while (TaskQueue.empty())
	{
		TaskQueueMutex->unlock();
		TerminatedMutex->lock();
		if (Terminated)
		{
			TerminatedMutex->unlock();
			return NULL;
		}
		TerminatedMutex->unlock();
		TaskQueueMutex->lock();
	}
	Task *task_ = TaskQueue.front();
	TaskQueue.pop_front();
	TaskQueueMutex->unlock();
	return task_;
}

bool	ThreadPool_::getTerminated()
{
	AutoMutex	am(TerminatedMutex);
	return Terminated;
}

void	ThreadPool_::setTerminated(bool _terminated)
{
	AutoMutex	am(TerminatedMutex);
	Terminated = _terminated;
}

void	*ThreadPoolRoutine(void *param)
{
	ThreadPool_ *t = ThreadPool_::getInstance();
	Task *task;
	while ((task = t->QueuePop(NULL)) != NULL)
		t->TaskExec(task);
	return NULL;
}
