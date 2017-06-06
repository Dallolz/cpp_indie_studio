#ifndef BOMB_HH_
# define BOMB_HH_

#include <time.h>
#include "irrlicht.h"
#include "Object.hh"

class	Bomb : public Object {

private:
  int	x;
  int	y;
  long	color;
  int	range;
  irr::u32	time;
  bool	isExplode;

public:
  Bomb(int x, int y, int range, long color, irr::u32 time);
  ~Bomb();

  int	  getX() const;
  int	  getY() const;
  long	getColor() const;
  int	  getRange() const;
  irr::u32	getTime() const;
  void	setIsExplode(bool isExplode);
  bool	getIsExplode() const;
};

#endif /* !BOMB_HH_ */
