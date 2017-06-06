#include "Gameplay.hpp"
#include "Block.hh"

void	Gameplay::drawChar1(float x, float z){
  if (!this->characters[0]->getAlive())
    {
      this->Char1->setVisible(false);
      return ;
    }
  if (!this->isDrawChar)
    {
      this->Char1 = this->sceneManager->addAnimatedMeshSceneNode(this->sceneManager->getMesh("./assets/models/sydney.md2"), 0, -1, irr::core::vector3df(x - 0.5, 0.0f, z - 0.5), irr::core::vector3df(0, 270, 180), irr::core::vector3df(0.05, 0.05, 0.05));
      this->Char1->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->Char1->setMaterialTexture(0, this->driver->getTexture("./assets/models/sydney.bmp"));
      this->Char1->setMD2Animation(irr::scene::EMAT_STAND);
      this->char1Animation = false;
    }
  else
    {
      irr::core::vector3df v = this->Char1->getPosition();
      irr::core::vector3df r = this->Char1->getRotation();
      if (v.X > x - 0.5)
	r.Y = 0;
      if (v.X < x - 0.5)
	r.Y = 180;
      if (v.Z > z - 0.5)
	r.Y = 90;
      if (v.Z < z - 0.5)
        r.Y = 270;
      if (v.X > x - 0.5 || v.X < x - 0.5 || v.Z > z - 0.5 || v.Z < z - 0.5)
	{
	  if (this->char1Animation == false)
	    {
	      this->Char1->setMD2Animation(irr::scene::EMAT_RUN);
	      this->char1Animation = true;
	    }
	}
      else
	{
	  if (this->char1Animation == true)
	    {
	      this->Char1->setMD2Animation(irr::scene::EMAT_STAND);
	      this->char1Animation = false;
	    }
	}
      v.X = x - 0.5;
      v.Z = z - 0.5;
      this->Char1->setPosition(v);
      this->Char1->setRotation(r);
    }
}

void	Gameplay::drawChar2(float x, float z){
  if (!this->characters[1]->getAlive())
    {
      this->Char2->setVisible(false);
      return ;
    }
  if (!this->isDrawChar)
    {
      this->Char2 = this->sceneManager->addAnimatedMeshSceneNode(this->sceneManager->getMesh("./assets/models/ninja.b3d"), 0, -1, irr::core::vector3df(x - 0.5, 0.0f, z - 0.5), irr::core::vector3df(0, 0, 180), irr::core::vector3df(0.2, 0.2, 0.2));
      this->Char2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->Char2->setMaterialTexture(0, this->driver->getTexture("./assets/models/nskinrd.jpg"));
      this->Char2->setFrameLoop(208, 300);
      this->Char2->setAnimationSpeed(15);
      this->char2Animation = false;
    }
  else
    {
      irr::core::vector3df v = this->Char2->getPosition();
      irr::core::vector3df r = this->Char2->getRotation();
      if (v.X > x - 0.5)
        r.Y = 90;
      if (v.X < x - 0.5)
	r.Y = 270;
      if (v.Z > z - 0.5)
        r.Y = 180;
      if (v.Z < z - 0.5)
	r.Y = 0;
      if (v.X > x - 0.5 || v.X < x - 0.5 || v.Z > z - 0.5 || v.Z < z - 0.5)
        {
          if (this->char2Animation == false)
            {
	      this->Char2->setFrameLoop(0, 13);
              this->char2Animation = true;
            }
        }
      else
        {
          if (this->char2Animation == true)
            {
              this->Char2->setFrameLoop(208, 300);
              this->char2Animation = false;
            }
        }
      v.X = x - 0.5;
      v.Z = z - 0.5;
      this->Char2->setPosition(v);
      this->Char2->setRotation(r);
    }
}

void    Gameplay::drawChar3(float x, float z){
  if (!this->characters[2]->getAlive())
    {
      this->Char3->setVisible(false);
      return ;
    }
  if (!this->isDrawChar)
    {
      this->Char3 = this->sceneManager->addAnimatedMeshSceneNode(this->sceneManager->getMesh("./assets/models/faerie.md2"), 0, -1, irr::core::vector3df(x - 0.5, 0.0f, z - 0.5), irr::core::vector3df(0, 270, 180), irr::core::vector3df(0.05, 0.05, 0.05));
      this->Char3->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->Char3->setMaterialTexture(0, this->driver->getTexture("./assets/models/faerie2.bmp"));
      this->Char3->setMD2Animation(irr::scene::EMAT_STAND);
      this->char3Animation = false;
    }
  else
    {
      irr::core::vector3df v = this->Char3->getPosition();
      irr::core::vector3df r = this->Char3->getRotation();
      if (v.X > x - 0.5)
        r.Y = 0;
      if (v.X < x - 0.5)
        r.Y = 180;
      if (v.Z > z - 0.5)
        r.Y = 90;
      if (v.Z < z - 0.5)
        r.Y = 270;
      if (v.X > x - 0.5 || v.X < x - 0.5 || v.Z > z - 0.5 || v.Z < z - 0.5)
        {
          if (this->char3Animation == false)
            {
              this->Char3->setMD2Animation(irr::scene::EMAT_RUN);
              this->char3Animation = true;
            }
        }
      else
        {
          if (this->char3Animation == true)
            {
              this->Char3->setMD2Animation(irr::scene::EMAT_STAND);
              this->char3Animation = false;
            }
        }
      v.X = x - 0.5;
      v.Z = z - 0.5;
      this->Char3->setPosition(v);
      this->Char3->setRotation(r);
    }
}

void    Gameplay::drawChar4(float x, float z){
  if (!this->characters[3]->getAlive())
    {
      this->Char4->setVisible(false);
      return ;
    }
  if (!this->isDrawChar)
    {
      this->Char4 = this->sceneManager->addAnimatedMeshSceneNode(this->sceneManager->getMesh("./assets/models/ninja.b3d"), 0, -1, irr::core::vector3df(x - 0.5, 0.0f, z - 0.5), irr::core::vector3df(0, 0, 180), irr::core::vector3df(0.2, 0.2, 0.2));
      this->Char4->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->Char4->setFrameLoop(208, 300);
      this->Char4->setAnimationSpeed(15);
      this->char4Animation = false;
    }
  else
    {
      irr::core::vector3df v = this->Char4->getPosition();
      irr::core::vector3df r = this->Char4->getRotation();
      if (v.X > x - 0.5)
        r.Y = 90;
      if (v.X < x - 0.5)
        r.Y = 270;
      if (v.Z > z - 0.5)
        r.Y = 180;
      if (v.Z < z - 0.5)
        r.Y = 0;
      if (v.X > x - 0.5 || v.X < x - 0.5 || v.Z > z - 0.5 || v.Z < z - 0.5)
        {
          if (this->char4Animation == false)
            {
              this->Char4->setFrameLoop(0, 13);
              this->char4Animation = true;
            }
        }
      else
        {
          if (this->char4Animation == true)
            {
              this->Char4->setFrameLoop(208, 300);
              this->char4Animation = false;
            }
        }
      v.X = x - 0.5;
      v.Z = z - 0.5;
      this->Char4->setPosition(v);
      this->Char4->setRotation(r);
    }
}

void  Gameplay::drawBackground() {

  this->driver->draw2DImage(driver->getTexture(this->background), position2d<s32>(0,0), rect<s32>(0,0,1280,720), 0, video::SColor(255,255,255,255), true);
}

void	Gameplay::drawObject()
{
  int	i;

  if (!isDraw)
    {
      i = 0;
      while (i < x * y)
	{
	  if (map[i / x][i % x].getObject() && map[i / x][i % x].getObject()->getType() == BLOCK && dynamic_cast<Block *>(map[i / x][i % x].getObject())->getSolid() == false)
	    {
	      mapDraw[i / x][i % x] = this->sceneManager->addCubeSceneNode(0.8f, 0, -1, irr::core::vector3df(i % x, 0.0f, i / x));
	      mapDraw[i / x][i % x]->setMaterialTexture(0, this->driver->getTexture("./assets/images/woodcrate.saad"));
	      mapDraw[i / x][i % x]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	      mapDraw[i / x][i % x]->setVisible(true);
	    }
	  else if (map[i / x][i % x].getObject() && map[i / x][i % x].getObject()->getType() == BLOCK && dynamic_cast<Block *>(map[i / x][i % x].getObject())->getSolid() == true)
	    {
	      mapDraw[i / x][i % x] = this->sceneManager->addCubeSceneNode(0.8f, 0, -1, irr::core::vector3df(i % x, 0.0f, i / x));
              mapDraw[i / x][i % x]->setMaterialTexture(0, this->driver->getTexture("./assets/images/rockwall.jpg"));
              mapDraw[i / x][i % x]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
              mapDraw[i / x][i % x]->setVisible(true);
	    }
	  else
	    mapDraw[i / x][i % x] = NULL;
	  i = i + 1;
	}
    }

  if (!this->characters.empty())
    this->drawChar1(this->characters[0]->getX() / 10, this->characters[0]->getY() / 10);
  if (this->characters.size() > 1)
    this->drawChar2(this->characters[1]->getX() / 10, this->characters[1]->getY() / 10);
  if (this->characters.size() > 2)
    this->drawChar3(this->characters[2]->getX() / 10, this->characters[2]->getY() / 10);
  if (this->characters.size() > 3)
    this->drawChar4(this->characters[3]->getX() / 10, this->characters[3]->getY() / 10);
  i = 0;
  while (i < x * y) {
    if (mapDraw[i / x][i % x] && !map[i / x][i % x].getObject())
      mapDraw[i / x][i % x]->setVisible(false);
    if (map[i / x][i % x].getObject() && map[i / x][i % x].getObject()->getType() == BOMB && (!mapDraw[i / x][i % x] || !mapDraw[i / x][i % x]->isVisible()))
      {
	mapDraw[i / x][i % x] = this->sceneManager->addSphereSceneNode(0.4f, 16, 0, -1, irr::core::vector3df(i % x, 0.0f, i / x));
	mapDraw[i / x][i % x]->setMaterialTexture(0, this->driver->getTexture("./assets/images/wall.bmp"));
	mapDraw[i / x][i % x]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	mapDraw[i / x][i % x]->setVisible(true);
      }
    i = i + 1;
  }
}
