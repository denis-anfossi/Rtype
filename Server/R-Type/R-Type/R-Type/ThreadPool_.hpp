#ifndef		THREAD_POOL_HPP
#define		THREAD_POOL_HPP

#ifdef __linux__
#include	"Thread/UnixThread.hpp"
#else
#include	"Thread\WinThread.hpp"
#endif
#include	"AutoMutex.hpp"

#include	<queue>
#include	<deque>
#include	<vector>

struct	Task
{
	void	(*function)(void *);
	void	*data;
};

class ThreadPool_
{
private:
	ThreadPool_(void);
	~ThreadPool_(void);

public:
	bool	ThreadPoolInit(int nbThreads);
	void	ThreadPoolDestroy();
	void	TaskExec(Task *task);
	bool	ThreadPush();
	bool	ThreadPop();
	void	QueuePush(void (*function)(void *), void *param);
	Task	*QueuePop(Task *task);
	bool	getTerminated();
	void	setTerminated(bool _terminated);

	static ThreadPool_	*getInstance(void);
	static void		kill(void);

private:
public:
	IMutex	*ThreadQueueMutex;
	IMutex	*TaskQueueMutex;
	IMutex	*TerminatedMutex;

	std::deque<Task *>	TaskQueue;
	std::deque<IThread *>	ThreadQueue;
	bool	Terminated;

//	static IMutex *_singletonMutex;
	static ThreadPool_	*_singleton;
};

	void	*ThreadPoolRoutine(void *param);

#endif		/* THREAD_POOL_HPP */
