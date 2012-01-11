#ifdef __linux__
#include "LinuxDynLib.hpp"
#include "circle.h"
#endif

#ifdef WIN32
#include <Windows.h>
#include "WindowsDynLib.hpp"
typedef int (*AddFunc)(int,int);
typedef void (*FunctionFunc)();
#endif

int main(int ac, char **av)
{
  IDynLib* lib;
#ifdef WIN32
  lib = new WindowsDynLib();
  AddFunc _AddFunc;
  FunctionFunc _FunctionFunc;
  Test *(*creator)();
  Test *myTest;
  void *tmp;
  
  lib->setlibName("creatdll.dll");
  lib->setHandleOpen((HINSTANCE)(lib->openLib()));
  if (lib->getHandleOpen())
    {
      //Test avec une class
      lib->setSymbolName("getInstanceDLL");
      tmp = lib->dlSymb();
      creator = reinterpret_cast<Test*  (*) ()>(tmp);
      myTest = creator();
      std::cout << "Resultat = " << myTest->AddTest(1,2) << std::endl;
      //
      lib->setSymbolName("Add");
      _AddFunc = (AddFunc)lib->dlSymb();
      lib->setSymbolName("Function");
      _FunctionFunc = (FunctionFunc)lib->dlSymb();
      if (_AddFunc)
	std::cout << "23 = 43 = " << _AddFunc(23, 43) << std::endl;
      if (_FunctionFunc)
	_FunctionFunc();
      lib->closeLib();
    }
  else
    std::cout << "DLL Failed To Load!" << std::endl;
  std::cin.get();
  return 0;
#else
  lib = new LinuxDynLib();
  
  void (*func)();
  void *creat;
  circle *my_cyrcle;
  circle *(*creator)();
  
  lib->setlibName("./libcircle.so");
  //lib.setflagOpen(RTLD_LAZY);
  lib->setSymbolName("make_circle");
  lib->setHandleOpen(lib->openLib());
  creat = lib->dlSymb();
  creator = reinterpret_cast<circle*  (*) ()>(creat);
  circle* my_circle = creator();
  
  my_circle->draw();
#endif
}
