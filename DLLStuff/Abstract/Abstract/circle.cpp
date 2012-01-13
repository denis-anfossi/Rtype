#include "circle.h"

using namespace std;

void circle::draw()
{
  cout << "   ###   " << endl;
  cout << "  #   #  " << endl;
  cout << " #     # " << endl;
  cout << " #     # " << endl;
  cout << "  #   #  " << endl;
  cout << "   ###   " << endl;
}

extern "C"
{
  circle *make_circle()
  {
    return new circle();
  }
}
