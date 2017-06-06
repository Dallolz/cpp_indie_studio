#include <stdlib.h>
#include "Square.hh"

Square::Square()
{
  this->x = 0;
  this->y = 0;
  this->object = NULL;
}

Square::~Square()
{

}

int	Square::getX() const
{
  return (x);
}

void	Square::setX(int x)
{
  this->x = x;
}

int	Square::getY() const
{
  return (y);
}

void	Square::setY(int y)
{
  this->y = y;
}

Object	*Square::getObject() const
{
  return (object);
}

void	Square::setObject(Object *object)
{
  this->object = object;
}

