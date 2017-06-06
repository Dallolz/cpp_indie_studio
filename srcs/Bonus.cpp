#include "Bonus.hh"

Bonus::Bonus(BonusType type)
{
  this->bonusType = type;
}

Bonus::~Bonus()
{

}

BonusType	Bonus::getBonusType() const
{
  return (bonusType);
}
