#ifndef CHARACTER_HH_
# define CHARACTER_HH_

#include <list>
#include <vector>
#include "Square.hh"
#include "Bomb.hh"

enum {
  PLAYER = 0,
  BOT
};

class	Character
{
private:
  float	x;
  float	y;
  long	color;
  int	speed;
  int	range;
  int	maxBombs;
  std::list<Bomb>	bombs;
  const std::vector<std::vector<Square> >	*map;
  bool	alive;
  irr::IrrlichtDevice	*device;
  int type;
public:
  Character(long color, float x, float y, const std::vector<std::vector<Square> > *map, irr::IrrlichtDevice *device, int type);
  ~Character();
  int  getType() const;
  long	getColor() const;
  int	getSpeed() const;
  int	getRange() const;
  int	getMaxBombs() const;
  float getX() const;
  float	getY() const;
  void	boostSpeed();
  void	boostRange();
  void	boostMaxBombs();
  std::list<Bomb> const	&getBombs() const;
  void	bombing();
  bool	canGoUp();
  bool  canGoDown();
  bool  canGoLeft();
  bool  canGoRight();
  bool  canGoUpLeft();
  bool  canGoDownRight();
  bool  canGoDownLeft();
  bool  canGoUpRight();
  void	mayGoUp();
  void  mayGoDown();
  void  mayGoLeft();
  void  mayGoRight();
  void	goUp();
  void	goDown();
  void	goLeft();
  void	goRight();
  bool	getAlive() const;
  void	setAlive(bool alive);
};

#endif /* !CHARACTER_HH_ */
