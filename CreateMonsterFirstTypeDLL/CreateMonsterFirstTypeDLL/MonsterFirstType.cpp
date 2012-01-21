#define	DLL_EXPORT
#include "MonsterFirstType.hpp"

MonsterFirstType::MonsterFirstType(int x, int y): x(x), y(y)
{
  type = 0;
  life = 1;
  srand(time(NULL));
  int res = rand() % 850;
  if(res < 800)
    {
      while(res < 800)
	res = rand() % 850;
      this->x = res;
    }
  else
    this->x = res;
  this->y = rand() % 300;
}

MonsterFirstType::~MonsterFirstType(void)
{ }

int16_t			MonsterFirstType::getX(void)
{
  return x;
}

int16_t			MonsterFirstType::getY(void)
{
  return y;
}

uint8_t			MonsterFirstType::getType(void)
{
  return type;
}

uint8_t			MonsterFirstType::getWidth(void)
{
  return width;
}

uint8_t			MonsterFirstType::getHeight(void)
{
  return height;
}

uint8_t			MonsterFirstType::getLife(void)
{
  return life;
}

void			MonsterFirstType::setLife(uint8_t lif)
{
  life = lif;
}

void			MonsterFirstType::update(void)
{
  int16_t ValX = getX();
  int16_t ValY = getY();
  static int mode = 1;

  if (y <= 70)
    mode = 0;
  if (y >= 530)
    mode = 1;
  if (mode == 1)
    ValY-=2;
  if (mode == 0) 
    ValY+=2;
  ValX -= 1;
  x = ValX;
  y = ValY;
}

void			MonsterFirstType::update2(void)
{

}

uint32_t		MonsterFirstType::getId(void)
{
  return id;
}

void			MonsterFirstType::setId(uint32_t _id)
{
  id = _id;
}

void			MonsterFirstType::ActFire()
{ }

void			MonsterFirstType::UpdateFire()
{ }

std::vector<_fires>     MonsterFirstType::getFires(void)
{
  return fires;
}

_fires                  MonsterFirstType::getFire(unsigned int j)
{
  return fires[j];
}

#define DECLDIR __declspec(dllexport)

extern "C"
{
#ifdef	__linux__
  void	*getInstanceDLL(int x, int y)
  {
    return	static_cast<void *>(new MonsterFirstType(x, y));
  }
#else
  void DECLDIR *getInstanceDLL(int x, int y)
  {
    return	static_cast<void *>(new MonsterFirstType(x, y));
  }
#endif
}
