#include "Object.hh"

Object::Object()
{
  type = OBJECT;
}

Object::~Object()
{

}

void	Object::setType(ObjectType type)
{
  this->type = type;
}

ObjectType	Object::getType() const
{
  return (type);
}
