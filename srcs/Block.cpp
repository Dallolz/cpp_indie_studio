#include <stdlib.h>
#include "Block.hh"
#include "Bonus.hh"

Block::Block()
{
  bonus = NULL;
  solid = true;
}

Block::Block(int i)
{
  bonus = NULL;
  solid = false;
}

Block::~Block()
{

}

Bonus	*Block::getBonus() const
{
  return (bonus);
}

void	Block::setBonus(Bonus *bonus)
{
  this->bonus = bonus;
}

bool  Block::getSolid() const
{
  return (solid);
}
