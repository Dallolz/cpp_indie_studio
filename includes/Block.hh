#ifndef BLOCK_HH_
# define BLOCK_HH_

#include "Bonus.hh"

class	Block : public Object
{
private:
  Bonus	*bonus;
  bool	solid;
public:
  Block();
  Block(int i);
  ~Block();
  Bonus *getBonus() const;
  void	setBonus(Bonus *bonus);
  bool	getSolid() const;
};

#endif /* !BLOCK_HH_ */
