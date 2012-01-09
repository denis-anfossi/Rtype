#include	"Server.hpp"

int     main()
{
  Server	s;
  try {
    s.init();
  }
  catch (int e) {
    std::cout << "Error: Init socket fail. Server will quit." << std::endl;
    return (0);
  }
  s.running();
  return (0);
}
