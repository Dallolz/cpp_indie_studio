# include <iostream>
# include <sys/time.h>
# include "Gameplay.hpp"
# include "Block.hh"

int   Gameplay::getX() const
{
  return (x);
}

int   Gameplay::getY() const
{
  return (y);
}

std::vector<std::vector<Square> > const	&Gameplay::getMap() const
{
  return (map);
}

void  Gameplay::setCharacters(std::vector<Character *> *characters) {
  this->characters = *characters;
}

std::vector<Character *> const	&Gameplay::getCharacters() const
{
  return (this->characters);
}

void  Gameplay::addCharacter(Character *character)
{
  this->characters.push_back(character);
}

#include <unistd.h>

void	Gameplay::affMapOnConsole()
{
  int	i;
  std::cout << std::endl << this->characters[0]->getBombs().size() << std::endl;
  std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
  i = 0;
  while (i < x * y) {
      if (!(i % x))
		std::cout << std::endl;
      if (map[i / x][i % x].getObject() && map[i / x][i % x].getObject()->getType() == BOMB)
		std::cout << "¤";
      else if (!this->characters.empty() && this->getCharacters()[0]->getAlive() && (int)(this->characters[0]->getX() / 10) == i % x && (int)(this->characters[0]->getY() / 10) == i / x)
		std::cout << "1";
      else if (this->characters.size() > 1 && this->getCharacters()[1]->getAlive() && (int)(this->characters[1]->getX() / 10) == i % x && (int)(this->characters[1]->getY() / 10) == i / x)
	std::cout << "2";
      else if (map[i / x][i % x].getObject() && map[i / x][i % x].getObject()->getType() == BONUS)
		std::cout << "B";
      else if (map[i / x][i % x].getObject())
		std::cout << "X";
      else
		std::cout << "'";
      i = i + 1;
    }
  std::cout << std::endl;
  usleep(5000);
}

void	Gameplay::explode(Bomb *bomb)
{
  int	i;
  int	j;
  int	touch;

  if (bomb->getIsExplode())
    return ;
  bomb->setIsExplode(true);
  if (mapDraw[bomb->getY()][bomb->getX()])
    mapDraw[bomb->getY()][bomb->getX()]->remove();
  mapDraw[bomb->getY()][bomb->getX()] = NULL;
  j = 0;
  while (j < this->characters.size())
    {
      if ((int)(this->characters[j]->getX() / 10) == bomb->getX() && (int)(this->characters[j]->getY() / 10) == bomb->getY())
	this->characters[j]->setAlive(false);
      j = j + 1;
    }
  i = bomb->getX() - 1;
  touch = 0;
  while (i >= 0 && i >= bomb->getX() - bomb->getRange() && (!map[bomb->getY()][i].getObject() || map[bomb->getY()][i].getObject()->getType() != BLOCK || dynamic_cast<Block *>(map[bomb->getY()][i].getObject())->getSolid() == false) && !touch)
    {
      j = 0;
      while (j < this->characters.size())
	{
	  if ((int)(this->characters[j]->getX() / 10) == i && (int)(this->characters[j]->getY() / 10) == bomb->getY())
	    this->characters[j]->setAlive(false);
	  j = j + 1;
	}
      if (map[bomb->getY()][i].getObject())
	{
	  Object    *object =  const_cast<Object *>(map[bomb->getY()][i].getObject());
	  if (map[bomb->getY()][i].getObject()->getType() == BOMB)
	    {
	      j = 0;
	      while (j < this->characters.size())
		{
		  std::list<Bomb>   *bombs = const_cast<std::list<Bomb> *>(&getCharacters()[j]->getBombs());
		  std::list<Bomb>::iterator	it;
		  for (it = bombs->begin(); it != bombs->end() && (it->getX() != i || it->getY() != bomb->getY()); ++it);
		  if (it != bombs->end())
		    bombs->erase(it);
		  j = j + 1;
		}
	      touch = 1;
              explode(dynamic_cast<Bomb *>(object));
	    }
	  if (map[bomb->getY()][i].getObject() && (map[bomb->getY()][i].getObject()->getType() != BLOCK || !dynamic_cast<Block *>(map[bomb->getY()][i].getObject())->getBonus()))
	    map[bomb->getY()][i].setObject(NULL);
	  else if (map[bomb->getY()][i].getObject())
	    {
	      map[bomb->getY()][i].setObject(dynamic_cast<Block *>(map[bomb->getY()][i].getObject())->getBonus());
	      if (dynamic_cast<Bonus *>(map[bomb->getY()][i].getObject())->getBonusType() == BOOTS)
		mapDraw[bomb->getY()][i]->setMaterialTexture(0, this->driver->getTexture("./assets/images/boots.jpg"));
	      else if (dynamic_cast<Bonus *>(map[bomb->getY()][i].getObject())->getBonusType() == FLAME)
		mapDraw[bomb->getY()][i]->setMaterialTexture(0, this->driver->getTexture("./assets/images/flame.jpg"));
	      else if (dynamic_cast<Bonus *>(map[bomb->getY()][i].getObject())->getBonusType() == BOMBUP)
		mapDraw[bomb->getY()][i]->setMaterialTexture(0, this->driver->getTexture("./assets/images/bombup.jpg"));
	    }
	  if (map[bomb->getY()][i].getObject() && map[bomb->getY()][i].getObject()->getType() != BOMB)
	    delete    object;
	  touch = 1;
	}
      i = i - 1;
    }
  i = bomb->getX() + 1;
  touch = 0;
  while (i <= 12 && i <= bomb->getX() + bomb->getRange() && (!map[bomb->getY()][i].getObject() || map[bomb->getY()][i].getObject()->getType() != BLOCK || dynamic_cast<Block *>(map[bomb->getY()][i].getObject())->getSolid() == false) && !touch)
    {
      j = 0;
      while (j < this->characters.size())
        {
          if ((int)(this->characters[j]->getX() / 10) == i && (int)(this->characters[j]->getY() / 10) == bomb->getY())
            this->characters[j]->setAlive(false);
          j = j + 1;
        }
      if (map[bomb->getY()][i].getObject())
        {
          Object    *object =  const_cast<Object *>(map[bomb->getY()][i].getObject());
          if (map[bomb->getY()][i].getObject()->getType() == BOMB)
            {
	      j = 0;
              while (j < this->characters.size())
                {
		  std::list<Bomb>   *bombs = const_cast<std::list<Bomb> *>(&getCharacters()[j]->getBombs());
		  std::list<Bomb>::iterator     it;
                  for (it = bombs->begin(); it != bombs->end() && (it->getX() != i || it->getY() != bomb->getY()) ; ++it);
                  if (it != bombs->end())
                    bombs->erase(it);
                  j = j + 1;
                }
	      touch = 1;
	      explode(dynamic_cast<Bomb *>(object));
            }
          if (map[bomb->getY()][i].getObject() && (map[bomb->getY()][i].getObject()->getType() != BLOCK || !dynamic_cast<Block *>(map[bomb->getY()][i].getObject())->getBonus()))
	    {
	      map[bomb->getY()][i].setObject(NULL);
	    }
          else if (map[bomb->getY()][i].getObject())
	    {
	      map[bomb->getY()][i].setObject(dynamic_cast<Block *>(map[bomb->getY()][i].getObject())->getBonus());
	      if (dynamic_cast<Bonus *>(map[bomb->getY()][i].getObject())->getBonusType() == BOOTS)
                mapDraw[bomb->getY()][i]->setMaterialTexture(0, this->driver->getTexture("./assets/images/boots.jpg"));
              else if (dynamic_cast<Bonus *>(map[bomb->getY()][i].getObject())->getBonusType() == FLAME)
                mapDraw[bomb->getY()][i]->setMaterialTexture(0, this->driver->getTexture("./assets/images/flame.jpg"));
	      else if (dynamic_cast<Bonus *>(map[bomb->getY()][i].getObject())->getBonusType() == BOMBUP)
		mapDraw[bomb->getY()][i]->setMaterialTexture(0, this->driver->getTexture("./assets/images/bombup.jpg"));

	    }
	  if (map[bomb->getY()][i].getObject() && map[bomb->getY()][i].getObject()->getType() != BOMB)
	    delete    object;
          touch = 1;
        }
      i = i + 1;
    }
  i = bomb->getY() - 1;
  touch = 0;
  while (i >= 0 && i >= bomb->getY() - bomb->getRange() && (!map[i][bomb->getX()].getObject() || map[i][bomb->getX()].getObject()->getType() != BLOCK || dynamic_cast<Block *>(map[i][bomb->getX()].getObject())->getSolid() == false) && !touch)
    {
      j = 0;
      while (j < this->characters.size())
        {
          if ((int)(this->characters[j]->getX() / 10) == bomb->getX() && (int)(this->characters[j]->getY() / 10) == i)
            this->characters[j]->setAlive(false);
          j = j + 1;
        }
      if (map[i][bomb->getX()].getObject())
        {
          Object    *object =  const_cast<Object *>(map[i][bomb->getX()].getObject());
          if (map[i][bomb->getX()].getObject()->getType() == BOMB)
            {
	      j = 0;
              while (j < this->characters.size())
                {
		  std::list<Bomb>   *bombs = const_cast<std::list<Bomb> *>(&getCharacters()[j]->getBombs());
		  std::list<Bomb>::iterator     it;
                  for (it = bombs->begin(); it != bombs->end() && (it->getX() != bomb->getX() || it->getY() != i) ; ++it);
                  if (it != bombs->end())
                    bombs->erase(it);
                  j = j + 1;
                }
	      touch = 1;
	      explode(dynamic_cast<Bomb *>(object));
            }
          if (map[i][bomb->getX()].getObject() && (map[i][bomb->getX()].getObject()->getType() != BLOCK || !dynamic_cast<Block *>(map[i][bomb->getX()].getObject())->getBonus()))
	    {
	      map[i][bomb->getX()].setObject(NULL);
	    }
          else if (map[i][bomb->getX()].getObject())
	    {
	      map[i][bomb->getX()].setObject(dynamic_cast<Block *>(map[i][bomb->getX()].getObject())->getBonus());
	      if (dynamic_cast<Bonus *>(map[i][bomb->getX()].getObject())->getBonusType() == BOOTS)
                mapDraw[i][bomb->getX()]->setMaterialTexture(0, this->driver->getTexture("./assets/images/boots.jpg"));
              else if (dynamic_cast<Bonus *>(map[i][bomb->getX()].getObject())->getBonusType() == FLAME)
                mapDraw[i][bomb->getX()]->setMaterialTexture(0, this->driver->getTexture("./assets/images/flame.jpg"));
              else if (dynamic_cast<Bonus *>(map[i][bomb->getX()].getObject())->getBonusType() == BOMBUP)
                mapDraw[i][bomb->getX()]->setMaterialTexture(0, this->driver->getTexture("./assets/images/bombup.jpg"));
	    }
	  if (map[i][bomb->getX()].getObject() && map[i][bomb->getX()].getObject()->getType() != BOMB)
	    delete    object;
          touch = 1;
        }
      i = i - 1;
    }
  i = bomb->getY() + 1;
  touch = 0;
  while (i <= 10 && i <= bomb->getY() + bomb->getRange() && (!map[i][bomb->getX()].getObject() || map[i][bomb->getX()].getObject()->getType() != BLOCK || dynamic_cast<Block *>(map[i][bomb->getX()].getObject())->getSolid() == false) && !touch)
    {
      j = 0;
      while (j < this->characters.size())
        {
          if ((int)(this->characters[j]->getX() / 10) == bomb->getX() && (int)(this->characters[j]->getY() / 10) == i)
            this->characters[j]->setAlive(false);
          j = j + 1;
        }
      if (map[i][bomb->getX()].getObject())
        {
          Object    *object =  const_cast<Object *>(map[i][bomb->getX()].getObject());
          if (map[i][bomb->getX()].getObject()->getType() == BOMB)
            {
	      j = 0;
	      std::list<Bomb>::iterator     it;
	      std::list<Bomb>   *bombs;
              while (j < this->characters.size())
                {
		  bombs = const_cast<std::list<Bomb> *>(&getCharacters()[j]->getBombs());
                  for (it = bombs->begin(); it != bombs->end() && (it->getX() != bomb->getX() || it->getY() != i) ; ++it);
                  j = j + 1;
                }
	      touch = 1;
	      explode(dynamic_cast<Bomb *>(object));
	      if (it != bombs->end())
		bombs->erase(it);
            }
          if (map[i][bomb->getX()].getObject() && (map[i][bomb->getX()].getObject()->getType() != BLOCK || !dynamic_cast<Block *>(map[i][bomb->getX()].getObject())->getBonus()))
	    {
	      map[i][bomb->getX()].setObject(NULL);
	    }
          else if (map[i][bomb->getX()].getObject())
	    {
	      map[i][bomb->getX()].setObject(dynamic_cast<Block *>(map[i][bomb->getX()].getObject())->getBonus());
	      if (dynamic_cast<Bonus *>(map[i][bomb->getX()].getObject())->getBonusType() == BOOTS)
                mapDraw[i][bomb->getX()]->setMaterialTexture(0, this->driver->getTexture("./assets/images/boots.jpg"));
              else if (dynamic_cast<Bonus *>(map[i][bomb->getX()].getObject())->getBonusType() == FLAME)
                mapDraw[i][bomb->getX()]->setMaterialTexture(0, this->driver->getTexture("./assets/images/flame.jpg"));
              else if (dynamic_cast<Bonus *>(map[i][bomb->getX()].getObject())->getBonusType() == BOMBUP)
                mapDraw[i][bomb->getX()]->setMaterialTexture(0, this->driver->getTexture("./assets/images/bombup.jpg"));
	    }
	  if (map[i][bomb->getX()].getObject() && map[i][bomb->getX()].getObject()->getType() != BOMB)
	    delete    object;
          touch = 1;
        }
      i = i + 1;
    }
}

bool  Gameplay::isNewHighScore(int newScore) const { 

  // Read score file, store all score in a vector.
  // Parse vector and compare each with newScore.
  // if newScore > vector[i], then return true;

  // If all vector have been parsed and newScore is < each member of vector,
  // return false;
  return (true);
}

void  Gameplay::majPosMesh() {
  int	i;
  int	j;

  i = 0;
  while (i < x * y)
    {
      if (map[i / x][i % x].getObject() && map[i / x][i % x].getObject()->getType() == BOMB)
	{
	  if (device->getTimer()->getRealTime() - dynamic_cast<Bomb *>(map[i / x][i % x].getObject())->getTime() > 2300)
	    {
	      j = 0;
              while (j < this->characters.size())
                {
		  std::list<Bomb>   *bombs = const_cast<std::list<Bomb> *>(&getCharacters()[j]->getBombs());
		  std::list<Bomb>::iterator     it;
                  for (it = bombs->begin(); it != bombs->end() && (it->getX() != i % x || it->getY() !=  i / x) ; ++it);
                  if (it != bombs->end())
                    bombs->erase(it);
                  j = j + 1;
                }
	      Object	*bomb =  const_cast<Object *>(map[i / x][i % x].getObject());
	      map[i / x][i % x].setObject(NULL);
	      explode(dynamic_cast<Bomb *>(bomb));
	      delete	bomb;
	    }
	}
      i = i + 1;
    }
  j = 0;
  while (j < this->characters.size())
    {
      if (getMap()[(int)(getCharacters()[j]->getY() / 10)][(int)(getCharacters()[j]->getX() / 10)].getObject() && getMap()[(int)(getCharacters()[j]->getY() / 10)][(int)(getCharacters()[j]->getX() / 10)].getObject()->getType() == BONUS)
        {
          if (dynamic_cast<Bonus *>(getMap()[(int)(getCharacters()[j]->getY() / 10)][(int)(getCharacters()[j]->getX() / 10)].getObject())->getBonusType() == BOMBUP)
        getCharacters()[j]->boostMaxBombs();
          else if (dynamic_cast<Bonus *>(getMap()[(int)(getCharacters()[j]->getY() / 10)][(int)(getCharacters()[j]->getX() / 10)].getObject())->getBonusType() == FLAME)
            getCharacters()[j]->boostRange();
          else if (dynamic_cast<Bonus *>(getMap()[(int)(getCharacters()[j]->getY() / 10)][(int)(getCharacters()[j]->getX() / 10)].getObject())->getBonusType() == BOOTS)
            getCharacters()[j]->boostSpeed();
          delete getMap()[(int)(getCharacters()[j]->getY() / 10)][(int)(getCharacters()[j]->getX() / 10)].getObject();
          
          Square    *square;
          square = const_cast<Square *>(&getMap()[(int)(getCharacters()[j]->getY() / 10)][(int)(getCharacters()[j]->getX() / 10)]);
          square->setObject(NULL);
	  if (mapDraw[(int)(getCharacters()[j]->getY() / 10)][(int)(getCharacters()[j]->getX() / 10)])
	    mapDraw[(int)(getCharacters()[j]->getY() / 10)][(int)(getCharacters()[j]->getX() / 10)]->remove();
	  mapDraw[(int)(getCharacters()[j]->getY() / 10)][(int)(getCharacters()[j]->getX() / 10)] = NULL;
        }
      j = j + 1;
    }
  j = 0;
  i = 0;
  while (j < this->characters.size())
    {
      if (this->characters[j]->getAlive())
	i = i + 1;
      j = j + 1;
    }
  if (i < 2)
    {
      device->getCursorControl()->setVisible(true);
      if (i < 1)
	{
	  this->guiEnv->addStaticText(L"End of the game:\nDraw !", irr::core::rect<irr::s32>(350,200,650,300), true, true, 0, -1, true);
	}
      else
	{
	  j = 0;
	  while (j < this->characters.size() && !this->characters[j]->getAlive())
	    j = j + 1;
	  wchar_t	s[35];
	  swprintf(s, 35, L"End of the game:\nPlayer %i win !", j + 1);
	  this->guiEnv->addStaticText(s, irr::core::rect<irr::s32>(350,200,650,300), true, true, 0, -1, true);
	}
      this->sceneManager->drawAll();
      this->guiEnv->drawAll();
      this->driver->endScene();
      sleep (5);
      if (isNewHighScore(0) && i > 0) {
        NewHighScore *highscore = new NewHighScore(this->device, this->soundEngine, this->scenesStack, this->device->getTimer()->getRealTime() - this->startTime);
        scenesStack->push(highscore);
      }
      else
	{
	  scenesStack->pop();
	  scenesStack->pop();
	}
    }
}

irr::u32	Gameplay::getTime() const
{
  return (startTime);
}
