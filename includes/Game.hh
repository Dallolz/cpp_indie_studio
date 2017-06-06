#ifndef GAME_HH_
# define GAME_HH_

#include <vector>
#include "Square.hh"
#include "Character.hh"

class	Game
{
private:
  std::vector<std::vector<Square> >	map;
  std::vector<Character *>	characters;
  int	x;
  int	y;
public:
  Game();
  Game(int x, int y);
  ~Game();
  int	getX() const;
  int	getY() const;
  std::vector<std::vector<Square> > const	&getMap() const;
  std::vector<Character *> const	&getCharacters() const;
  void	addCharacter(Character *character);
  void	affMapOnConsole();
  void  majPosMesh();
  void	explode(Bomb *bomb);
};

#endif /* !GAME_HH_ */
