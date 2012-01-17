#define	DLL_EXPORT
#include "MonsterFirstType.hpp"

MonsterFirstType::MonsterFirstType(int x, int y): x(x), y(y)
{ }

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



std::vector<int16_t>	MonsterFirstType::getXFires(void)
{
  return xFires;
}

std::vector<int16_t>	MonsterFirstType::getYFires(void)
{
  return yFires;
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

void			MonsterFirstType::update(void)
{
	
	static double ValX;
	static double ValY;

	y = sinf(ValX);
	x = ValX;
	ValX++;
	ValY++;
}

uint32_t		MonsterFirstType::getId(void)
{
	return id;
}

void			MonsterFirstType::setId(uint32_t _id)
{
	id = _id;
}

void			MonsterFirstType::move()
{
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
