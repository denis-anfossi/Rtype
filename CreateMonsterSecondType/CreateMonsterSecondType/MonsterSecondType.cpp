#define	DLL_EXPORT
#include "MonsterSecondType.hpp"

MonsterSecondType::MonsterSecondType(int x, int y)
{
  type = 1;
  life = 1;
  srand(time(NULL));
  modefire = rand() % 2;
  this->x = 805;
  this->y = 300;
}

MonsterSecondType::~MonsterSecondType(void)
{ }

int16_t			MonsterSecondType::getX(void)
{
  return x;
}

int16_t			MonsterSecondType::getY(void)
{
  return y;
}

uint8_t			MonsterSecondType::getLife(void)
{
  return life;
}

void			MonsterSecondType::setLife(uint8_t lif)
{
  life = lif;
}

uint8_t			MonsterSecondType::getType(void)
{
  return type;
}

uint8_t			MonsterSecondType::getWidth(void)
{
  return width;
}

uint8_t			MonsterSecondType::getHeight(void)
{
  return height;
}

void			MonsterSecondType::update(void)
{
  int16_t ValY = getY();
  int16_t ValX = getX();
  static int mode = 1;
  static int foot = 5;
  static int fire = 0;
  if (life > 0)
    {
      if ((fire++ % 48) == 0)
	addFire();
      if (modefire == 1)
	{
	  if (x >= 300)
	    {
	      x = ValX - 3;
	      y = ValY - 1;
	    }
	  else if (x >= 200 && x < 300)
	    {
	      x = ValX - 3;
	      y = ValY - 3;
	    }
	  else if (x >= 100 && x < 200)
            {
              x = ValX - 3;
              y = ValY - 5;
            }
	  else if (x >= 0 && x < 100)
            {
              x = ValX - 3;
              y = ValY - 7;
	    }
	}
      else
	{
	  if (x >= 300)
	    {
	      x = ValX - 3;
	      y = ValY + 1;
	    }
	  else if (x >= 200 && x < 300)
            {
              x = ValX - 3;
              y = ValY + 3;
            }
          else if (x >= 100 && x < 200)
            {
              x = ValX - 3;
              y = ValY + 5;
            }
          else if (x >= 0 && x < 100)
            {
              x = ValX - 3;
              y = ValY + 7;
	    }
	}
    }
  UpdateFire();
}

void			MonsterSecondType::update2(void)
{
  UpdateFire2();
}

uint32_t		MonsterSecondType::getId(void)
{
  return id;
}

void			MonsterSecondType::setId(uint32_t _id)
{
  id = _id;
}

void			MonsterSecondType::ActFire()
{
  if (life > 0)
    addFire();
}

void			MonsterSecondType::UpdateFire()
{
  for (unsigned int i = 0; i < fires.size(); ++i)
    {
      fires[i].x -= 10;
      if (fires[i].x < -30 && fires[i].alive == 1)
        fires[i].alive = 0;
    }
}

void			MonsterSecondType::UpdateFire2()
{
  for (unsigned int i = 0; i < fires.size(); ++i)
    {
      if (fires[i].alive == 0)
	deleteFire(i);
    }
}

std::vector<_fires>     MonsterSecondType::getFires(void)
{
  return fires;
}

_fires                  MonsterSecondType::getFire(unsigned int j)
{
  return fires[j];
}

void			MonsterSecondType::addFire(void)
{
  struct timeval        now;
  _fires                fire;
  fire.x = x - 2;
  fire.y = y + 32;
  gettimeofday(&now, NULL);
  fire.id = ((now.tv_sec % 10000) * 100000) + (now.tv_usec % 100000);
  fire.alive = 1;
  fires.push_back(fire);
}

void			MonsterSecondType::deleteFire(unsigned int i)
{
  if (i < fires.size())
    fires.erase(fires.begin()+i);
}

#ifndef __linux__

int             gettimeofday (struct timeval *tp, void *tz)
{
  struct _timeb timebuffer;
  _ftime_s(&timebuffer);
  tp->tv_sec = timebuffer.time;
  tp->tv_usec = timebuffer.millitm * 1000;
  return 0;
}

#endif

#define DECLDIR __declspec(dllexport)

extern "C"
{
#ifdef	__linux__
  void	*getInstanceDLL(int x, int y)
  {
    return	static_cast<void *>(new MonsterSecondType(x, y));
  }
#else
  void DECLDIR *getInstanceDLL(int x, int y)
  {
    return	static_cast<void *>(new MonsterSecondType(x, y));
  }
#endif
}
