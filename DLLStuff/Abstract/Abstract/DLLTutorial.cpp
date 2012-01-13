#include <iostream>
#define DLL_EXPORT
#include "DLLTutorial.h"

extern "C"
{
   int DECLDIR Add( int a, int b )
   {
      return( a + b );
   }

   void DECLDIR Function( void )
   {
      std::cout << "DLL Called!" << std::endl;
   }

   void DECLDIR *getInstanceDLL()
   {
	   return static_cast<void*> (new Test);
   }
}