#include <cstdint>

#ifndef		_FIRES_
#define		_FIRES_
#endif

#ifndef _IMONSTER_HPP_
#define _IMONSTER_HPP_

#include	<vector>

struct  _fires
{
  int16_t       x;
  int16_t       y;
  uint32_t      id;
  uint8_t       alive;
};

class	IMonster
{
public:
  virtual int16_t		getX(void) = 0;
  virtual int16_t		getY(void) = 0;
  virtual uint8_t		getType(void) = 0;
  virtual void			update(void) = 0;
  virtual void			update2(void) = 0;
  virtual uint8_t		getWidth(void) = 0;
  virtual uint8_t		getHeight(void) = 0;
  virtual uint8_t		getLife(void) = 0;
  virtual void			setLife(uint8_t) = 0;
  virtual uint32_t		getId(void) = 0;
  virtual void			setId(uint32_t _id) = 0;
  virtual void			ActFire(void) = 0;
  virtual void			UpdateFire(void) = 0;
  virtual std::vector<_fires>   getFires(void) = 0;
  virtual _fires                getFire(unsigned int j) = 0;
};

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

#endif	/* IMONSTER_HPP */
