#ifndef BONUS_HH_
# define BONUS_HH_

#include "Object.hh"

enum	BonusType
  {
    BOMBUP,
    FLAME,
    BOOTS
  };

class	Bonus : public Object
{
private:
  BonusType	bonusType;
public:
  Bonus(BonusType type);
  ~Bonus();
  BonusType	getBonusType() const;
};

#endif /* !BONUS_HH_ */
