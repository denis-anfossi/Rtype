#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <iostream>

class circle
{
 public:
  virtual void draw();
};

typedef circle *(*maker_circle)();
#endif
