#define	DLL_EXPORT
#include "MonsterSecondType.hpp"

MonsterSecondType::MonsterSecondType(int x, int y)
{ 
	type = 1;
	life = 1;
	srand(time(NULL));
	modefire = rand() % 2;
	int res = rand() % 850;
	if(res < 800)
	{
		while(res < 800)
			 res = rand() % 850;
		this->x = res;
	}
	else
		this->x = res;
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

std::vector<int16_t>	MonsterSecondType::getXFires(void)
{
  return xFires;
}

std::vector<int16_t>	MonsterSecondType::getYFires(void)
{
  return yFires;
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

	if(modefire == 1)
	{
		if(x >= 300)
		{
			x = ValX - 5;
			y = ValY - 1;
		}
		else if(x >= 200 && x < 300)
		{
			x = ValX - 1;
			y = ValY - 10;
		}
	}
	else
	{
		if(x >= 300)
		{
			x = ValX - 5;
			y = ValY + 1;
		}
		else if(x >= 200 && x < 300)
		{
			x = ValX - 1;
			y = ValY + 10;
		}
	}
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
	int16_t xfire = getX();
	int16_t yfire = getY();
	xFires.push_back(xfire);
	yFires.push_back(yfire);
}

void			MonsterSecondType::UpdateFire()
{
	std::vector<int16_t>::iterator itx = xFires.begin();
	std::vector<int16_t>::iterator ity = yFires.begin();
	while(itx != xFires.end())
	{
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
    return	static_cast<void *>(new MonsterSecondType(x, y));
  }
#else
  void DECLDIR *getInstanceDLL(int x, int y)
  {
    return	static_cast<void *>(new MonsterSecondType(x, y));
  }
#endif
}
