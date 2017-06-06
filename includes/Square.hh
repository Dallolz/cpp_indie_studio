#ifndef SQUARE_HH_
# define SQUARE_HH_

#include "Object.hh"

class	Square
{
private:
  int		x;
  int		y;
  Object	*object;
public:
  Square();
  ~Square();
  int	getX() const;
  void	setX(int x);
  int	getY() const;
  void	setY(int y);
  Object	*getObject() const;
  void	setObject(Object *object);
};

#endif /* !SQUARE_HH_ */
