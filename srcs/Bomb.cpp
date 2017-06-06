#include "Bomb.hh"

Bomb::Bomb(int x, int y, int range, long color, irr::u32 time)
{
  this->x = x;
  this->y = y;
  this->range = range;
  this->color = color;
  this->time = time;
  this->isExplode = false;
}

Bomb::~Bomb()
{

}

int	Bomb::getX() const
{
  return (x);
}

int	Bomb::getY() const
{
  return (y);
}

long 	Bomb::getColor() const
{
  return (color);
}

int	Bomb::getRange() const
{
  return (range);
}

irr::u32	Bomb::getTime() const
{
  return (time);
}

void	Bomb::setIsExplode(bool isExplode)
{
  this->isExplode = isExplode;
}

bool	Bomb::getIsExplode() const
{
  return (isExplode);
}
