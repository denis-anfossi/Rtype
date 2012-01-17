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
	int16_t ValX = getX();
	int16_t ValY = getY();
	static int mode = 1;

	if(y == 0)
		mode = 0;
	if(y == 600)
		mode = 1;
	if(mode == 1)
		ValY--;
	if(mode == 0) 
		ValY++;
	ValX++;
	x = ValX;
	y = ValY;
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
{
	int16_t xfire = getX();
	int16_t yfire = getY();
	xFires.push_back(xfire);
	yFires.push_back(yfire);
}

void			MonsterFirstType::UpdateFire()
{
	std::vector<int16_t>::iterator itx = xFires.begin();
	std::vector<int16_t>::iterator ity = yFires.begin();
	while(itx != xFires.end())
	{
		std::cout << "J'ai " << xFires.size() << " tires" << std::endl;
		if(xFires.size() > 0 && yFires.size() > 0)
		{
			if(*itx <= 0)
			{
				xFires.erase(itx);
				itx = xFires.begin();
				ity = yFires.begin();
			}
			else
			{
				std::cout << "Je decremente les x" << std::endl;
				*itx -= 1;
				std::cout << *itx << std::endl;
				++itx;
				++ity;
			}
		}
	}
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
