#ifndef		MONSTER_SECOND_TYPE_HPP
#define		MONSTER_SECOND_TYPE_HPP

#include	"IMonster.hpp"
#include	<time.h>
#include	<iostream>

class MonsterSecondType	: public IMonster
{
public:
  MonsterSecondType(int, int);
  ~MonsterSecondType(void);

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
  virtual void			ActFire();
  virtual void			UpdateFire();
  virtual std::vector<_fires>	getFires(void);
  virtual _fires		getFire(unsigned int i);
private:
  void				addFire(void);
  void				deleteFire(unsigned int i);
  void				UpdateFire2(void);

  uint32_t		id;
  uint8_t		width;
  uint8_t		height;
  uint8_t		type;
  uint8_t		fire;
  int16_t		x;
  int16_t		y;
  uint8_t		life;
  uint8_t		modefire;
  std::vector<_fires>	fires;
};

#ifdef __linux__
#include	<sys/time.h>
#else
#include	<Windows.h>
#include    <sys/timeb.h>
int     gettimeofday(struct timeval *tp, void *tz);
#endif

#endif	/* MONSTER_SECOND_TYPE_HPP */
