#ifndef		MONSTER_FIRST_TYPE_HPP
#define		MONSTER_FIRST_TYPE_HPP

#include	"IMonster.hpp"
#include	<iostream>
#include	<time.h>

class MonsterFirstType	: public IMonster
{
public:
  MonsterFirstType(int, int);
  ~MonsterFirstType(void);

  virtual int16_t		getX(void);
  virtual int16_t		getY(void);
  virtual uint8_t		getType(void);
  virtual void			update(void);
  virtual void			update2(void);
  virtual uint8_t		getWidth(void);
  virtual uint8_t		getHeight(void);
  virtual uint8_t		getLife(void);
  virtual void			setLife(uint8_t);
  virtual uint32_t		getId(void);
  virtual void			setId(uint32_t id);
  virtual void			ActFire(void);
  virtual void			UpdateFire(void);
  virtual std::vector<_fires>	getFires(void);
  virtual _fires		getFire(unsigned int j);
private:
  uint32_t		id;
  uint8_t		width;
  uint8_t		height;
  uint8_t		type;
  uint8_t		fire;
  int16_t		x;
  int16_t		y;
  uint8_t		life;
  uint8_t		modefire;
  std::vector<_fires>   fires;
};

#endif	/* MONSTER_FIRST_TYPE_HPP */
