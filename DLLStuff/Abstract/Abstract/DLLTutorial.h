#ifndef _DLL_TUTORIAL_H_
#define _DLL_TUTORIAL_H_
#include <iostream>

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

class Test
{
public:
	int AddTest(int a, int b)
	{
		return (a+b);
	}
};

extern "C"
{
   DECLDIR int Add( int a, int b );
   DECLDIR void Function( void );
   DECLDIR void* getInstanceDLL();
}

#endif