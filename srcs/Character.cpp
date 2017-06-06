#include <vector>
#include "Character.hh"
#include "Bomb.hh"

Character::Character(long color, float x, float y, const std::vector<std::vector<Square> > *map, irr::IrrlichtDevice *device, int type)
{
  this->color = color;
  this->x = x;
  this->y = y;
  this->speed = 1;
  this->range = 1;
  this->maxBombs = 1;
  this->map = map;
  this->alive = true;
  this->device = device;
  this->type = type;
}

Character::~Character()
{

}

int   Character::getType() const {
  return (type);
}

long	Character::getColor() const
{
  return (color);
}

int	Character::getSpeed() const
{
  return (speed);
}

int	Character::getRange() const
{
  return (range);
}

int	Character::getMaxBombs() const
{
  return (maxBombs);
}

float	Character::getX() const
{
  return (x);
}

float	Character::getY() const
{
  return (y);
}

void  Character::boostSpeed()
{
  if (speed < 5)
    speed += 1;
}

void  Character::boostRange()
{
  if (range < 5)
    range += 1;
}

void  Character::boostMaxBombs()
{
  if (maxBombs < 5)
    maxBombs += 1;
}

std::list<Bomb> const	&Character::getBombs() const
{
  return (bombs);
}

void	Character::bombing()
{
  std::list<Bomb>::iterator	it;

  if (this->bombs.size() >= this->maxBombs || map[0][(int)(y / 10)][(int)(x / 10)].getObject())
    return ;
Bomb	*bomb = new Bomb((int)(this->x) / 10, (int)(this->y) / 10, this->range, this->color, device->getTimer()->getRealTime());
  bomb->setType(BOMB);
  this->bombs.push_back(*bomb);
  Square    *square;
  square = const_cast<Square *>(&map[0][(int)(y / 10)][(int)(x / 10)]);
  square->setObject(bomb);
}

bool	Character::canGoUp()
{
  if ((int)x % 10 != 5)
    return (false);
  if ((!((int)(y / 10) - 1 < 0) && map[0][(int)(y / 10) - 1][(int)(x / 10)].getObject() && map[0][(int)(y / 10) - 1][(int)(x / 10)].getObject()->getType() != BONUS) && (int)y % 10 == 5)
    return (false);
  return (true);
}

bool    Character::canGoDown()
{
  if ((int)x % 10 != 5)
    return (false);
  if ((!((int)(y / 10) + 1 > 10) && map[0][(int)(y / 10) + 1][(int)(x / 10)].getObject() && map[0][(int)(y / 10) + 1][(int)(x / 10)].getObject()->getType() != BONUS) && (int)y % 10 == 5)
    return (false);
  return (true);
}

bool    Character::canGoLeft()
{
  if ((int)y % 10 != 5)
    return (false);
  if ((!((int)(x / 10) - 1 < 0) && map[0][(int)(y / 10)][(int)(x / 10) - 1].getObject() && map[0][(int)(y / 10)][(int)(x / 10) - 1].getObject()->getType() != BONUS) && (int)x % 10 == 5)
    return (false);
  return (true);
}

bool    Character::canGoRight()
{
  if ((int)y % 10 != 5)
    return (false);
  if ((!((int)(x / 10) + 1 > 12) && map[0][(int)(y / 10)][(int)(x / 10) + 1].getObject() && map[0][(int)(y / 10)][(int)(x / 10) + 1].getObject()->getType() != BONUS) && (int)x % 10 == 5)
    return (false);
  return (true);
}

bool	Character::canGoUpLeft()
{
  if ((int)(y / 10) - 1 < 0 || (int)(x / 10) - 1 < 0)
    return (false);
  if (map[0][(int)(y / 10) - 1][(int)(x / 10) - 1].getObject() && map[0][(int)(y / 10) - 1][(int)(x / 10) - 1].getObject()->getType() != BONUS)
    return (false);
  return (true);
}

bool	Character::canGoDownRight()
{
  if ((int)(y / 10) + 1 > 10 || (int)(x / 10) + 1 > 12)
    return (false);
  if (map[0][(int)(y / 10) + 1][(int)(x / 10) + 1].getObject() && map[0][(int)(y / 10) + 1][(int)(x / 10) + 1].getObject()->getType() != BONUS)
    return (false);
  return (true);
}

bool	Character::canGoDownLeft()
{
  if ((int)(y / 10) + 1 > 10 || (int)(x / 10) - 1 < 0)
    return (false);
  if (map[0][(int)(y / 10) + 1][(int)(x / 10) - 1].getObject() && map[0][(int)(y / 10) + 1][(int)(x / 10) - 1].getObject()->getType() != BONUS)
    return (false);
  return (true);
}

bool	Character::canGoUpRight()
{
  if ((int)(y / 10) - 1 < 0 || (int)(x / 10) + 1 > 12)
    return (false);
  if (map[0][(int)(y / 10) - 1][(int)(x / 10) + 1].getObject() && map[0][(int)(y / 10) - 1][(int)(x / 10) + 1].getObject()->getType() != BONUS)
    return (false);
  return (true);
}

void	Character::mayGoUp()
{
  if (!((int)(y / 10) - 1 < 0) && (!map[0][(int)(y / 10) - 1][(int)(x / 10)].getObject() || map[0][(int)(y / 10) - 1][(int)(x / 10)].getObject()->getType() == BONUS))
    {
      if ((int)x % 10 > 5)
 	goLeft();
      else
	goRight();
    }
  else
    {
      if ((int)x % 10 > 5 && canGoUpRight())
	goRight();
      else if ((int)x % 10 < 5 && canGoUpLeft())
 	goLeft();
    }
}

void    Character::mayGoDown()
{
  if (!((int)(y / 10) + 1 > 10) && (!map[0][(int)(y / 10) + 1][(int)(x / 10)].getObject() || map[0][(int)(y / 10) + 1][(int)(x / 10)].getObject()->getType() == BONUS))
    {
      if ((int)x % 10 > 5)
 	goLeft();
      else
 	goRight();
    }
  else
    {
      if ((int)x % 10 > 5 && canGoDownRight())
	goRight();
      else if ((int)x % 10 < 5 && canGoDownLeft())
	goLeft();
    }
}

void    Character::mayGoLeft()
{
  if (!((int)(x / 10) + 1 < 0) && (!map[0][(int)(y / 10)][(int)(x / 10) - 1].getObject() || map[0][(int)(y / 10)][(int)(x / 10) - 1].getObject()->getType() == BONUS))
    {
      if ((int)y % 10 > 5)
	goUp();
      else
	goDown();
    }
  else
    {
      if ((int)y % 10 > 5 && canGoDownLeft())
	goDown();
      else if ((int)y % 10 < 5 && canGoUpLeft())
	goUp();
    }
}

void    Character::mayGoRight()
{
  if (!((int)(x / 10) + 1 > 12) && (!map[0][(int)(y / 10)][(int)(x / 10) + 1].getObject() || map[0][(int)(y / 10)][(int)(x / 10) + 1].getObject()->getType() == BONUS))
    {
      if ((int)y % 10 > 5)
	goUp();
      else
	goDown();
    }
  else
    {
      if ((int)y % 10 > 5 && canGoDownRight())
	goDown();
      else if ((int)y % 10 < 5 && canGoUpRight())
	goUp();
    }
}

void  Character::goUp()
{
  if (y > 5)
    {
      if (canGoUp())
 		y = y - 1;
      else
	mayGoUp();
    }
  else
    y = 5;
}

void  Character::goDown()
{
  if (y < 105)
    {
      if (canGoDown())
 		y = y + 1;
      else
	mayGoDown();
    }
  else
    y = 105;
}

void  Character::goLeft()
{
  if (x > 5)
    {
      if (canGoLeft())
		x = x - 1;
      else
	mayGoLeft();
    }
  else
    x = 5;
}

void  Character::goRight()
{
  if (x < 125)
    {
      if (canGoRight())
  		x = x + 1;
      else
	mayGoRight();
    }
  else
    x = 125;
}

bool	Character::getAlive() const
{
  return (alive);
}

void	Character::setAlive(bool alive)
{
  this->alive = alive;
}
