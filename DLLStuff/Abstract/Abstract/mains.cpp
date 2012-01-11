#include <Windows.h>

#include "LinuxDynLib.hpp"
#include "circle.h"

typedef int (*AddFunc)(int,int);
typedef void (*FunctionFunc)();

int main(int ac, char **av)
{
#ifdef WIN32
  WindowsDynLib lib;


  AddFunc _AddFunc;
   FunctionFunc _FunctionFunc;
   //HINSTANCE hInstLibrary = LoadLibrary(L"creatdll.dll");
   HINSTANCE HandleOpen = (HINSTANCE)(lib.openLib());
   
   if (HandleOpen)
   {
      //_AddFunc = (AddFunc)GetProcAddress(hInstLibrary, "Add");
	   _AddFunc = (AddFunc)lib.dlSymb();
      _FunctionFunc = (FunctionFunc)GetProcAddress(hInstLibrary,
         "Function");

      if (_AddFunc)
         std::cout << "23 = 43 = " << _AddFunc(23, 43) << std::endl;
      if (_FunctionFunc)
         _FunctionFunc();

      FreeLibrary(hInstLibrary);
   }
   else
      std::cout << "DLL Failed To Load!" << std::endl;

   std::cin.get();

   return 0;
  #else
  LinuxDynLib lib;

  void (*func)();
  void *creat;
  circle *my_cyrcle;
  circle *(*creator)();

  lib.setlibName("./../libcircle.so");
  lib.setflagOpen(RTLD_LAZY);
  lib.setSymbolName("make_circle");
  lib.setHandleOpen(lib.openLib());
  creat = lib.dlSymb();
  creator = reinterpret_cast<circle*  (*) ()>(creat);
  circle* my_circle = creator();
  
  my_circle->draw();
  #endif
}