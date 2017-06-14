#include "Gameplay.hpp"
#include "Block.hh"

/*
**	Main menu. 
**	Scene description: At the bottom of the stack. Displayed after the splashscreen.
*/

/*
    Set the skin transparency by changing the alpha values of all skin-colors
*/

Gameplay::Gameplay(IrrlichtDevice *device, ISoundEngine *sound, std::stack<IScene *> *stack) { 
  this->device = device;
  this->soundEngine = sound;
  this->sceneManager = this->device->getSceneManager();
  this->guiEnv = this->device->getGUIEnvironment();
  this->driver = this->device->getVideoDriver();
  this->scenesStack = stack;
  this->music_loop = NULL;

  int   i;

  this->x = 13;
  this->y = 11;
  map.resize(y);
  mapDraw.resize(y);
  i = 0;
  while (i < x * y)
    {
      if (!(i % x))
	{
	  map[i / x].resize(x);
	  mapDraw[i / x].resize(x);
	}
      map[i / x][i % x].setY(i / x);
      map[i / x][i % x].setX(i % x);
      i = i + 1;
    }
}

Gameplay::~Gameplay() { }

IrrlichtDevice  *Gameplay::getDevice(void) { return (this->device); }
ISceneManager	*Gameplay::getSceneManager(void) { return (this->sceneManager); }
IGUIEnvironment	*Gameplay::getGUIEnv(void) { return (this->guiEnv); }
IVideoDriver	*Gameplay::getDriver(void) { return (this->driver); }
ISoundEngine    *Gameplay::getSoundEngine(void) { return (this->soundEngine); }
GEventReceiver  *Gameplay::getEventReceiver(void) { return (this->eventReceiver); }

void        Gameplay::setDevice(IrrlichtDevice *arg) { this->device = arg; }
void        Gameplay::setSceneManager(ISceneManager *arg) { this->sceneManager = arg; }
void        Gameplay::setGUIEnv(IGUIEnvironment *arg) { this->guiEnv = arg; }
void        Gameplay::setDriver(IVideoDriver *arg) { this->driver = arg; }
void        Gameplay::setSoundEngine(ISoundEngine *arg) { this->soundEngine = arg; }
void        Gameplay::setEventReceiver(GEventReceiver *arg) { this->eventReceiver = arg; }



/* 
** Step 2: INITIALIZATION
** Everything which need to be calculated only at the beginning of the scene.
** For example cameras, models, textures...
*/

void 	Gameplay::setBGMusic(int mapID) {

	const char 	*music[] = { "./assets/audio/music/gameplay_sky.ogg",
							"./assets/audio/music/gameplay_desert.ogg",
							"./assets/audio/music/gameplay_ocean.ogg",
							"./assets/audio/music/gameplay_volcano.ogg" };

	const io::path bg[] = { "./assets/images/background_sky.jpg",
									"./assets/images/background_desert.jpg",
									"./assets/images/background_ocean.jpeg",
									"./assets/images/background_volcano.jpg" };

	this->music_loop = this->soundEngine->play2D(music[mapID], true, false, true);
	this->background = bg[mapID];
}

void 	Gameplay::init(int *mapID) {

    this->sceneManager->clear();
    this->guiEnv->clear();
    this->soundEngine->stopAllSounds();

    if (!music_loop)
    	setBGMusic(*mapID);

    this->sceneManager->addCameraSceneNode(0,irr::core::vector3df(5.5f, -10.0f, 4.5f), irr::core::vector3df(5.5f, 0.0f, 4.6f), 0, true);
    if (this->eventReceiver = new GEventReceiver())
        device->setEventReceiver(this->eventReceiver);
    else
        throw std::string(strerror(ENOMEM));
    this->isDraw = false;
    this->isDrawChar = false;

    int   i;
    int   nbb;
    int   randbonus;

    nbb = 44;
    i = 0;
    while (i < x * y)
      {
	if ((i % x) % 2 == 1 && (i / x) % 2 == 1)
	  {
	    Block *block = new Block;
	    block->setType(BLOCK);
	    map[i / x][i % x].setObject(block);
	  }
	i = i + 1;
      }
    srand(time(NULL));
    while (nbb >= 4)
      {
	i = rand() % ((x * y / 4) + 2 + y / 2);
	if (i < (x * y / 4) - x / 2 + 1)
	  {
	    if (((i % (x / 2)) % 2 == 0 || (i / (x / 2)) % 2 == 0) && (i % (x / 2) > 1 || i / (x / 2) > 1) && map[i / (x / 2)][i % (x / 2)].getObject() == NULL)
	      {
		Block *block1 = new Block(0);
		Block *block2 = new Block(0);
		Block *block3 = new Block(0);
		Block *block4 = new Block(0);
		block1->setType(BLOCK);
		block2->setType(BLOCK);
		block3->setType(BLOCK);
		block4->setType(BLOCK);
		map[i / (x / 2)][i % (x / 2)].setObject(block1);
		map[i / (x / 2)][x - 1 - i % (x / 2)].setObject(block2);
		map[y - 1 - i / (x / 2)][i % (x / 2)].setObject(block3);
		map[y - 1 - i / (x / 2)][x - 1 - i % (x / 2)].setObject(block4);
		nbb = nbb - 4;
	      }
	  }
	else if (i >= (x * y / 4) - x / 2 + 1 && i < (x * y / 4) + 1 && map[5][i - ((x * y / 4) - x / 2 + 1)].getObject() == NULL)
	  {
	    i = i - ((x * y / 4) - x / 2 + 1);
	    if (i % 2 == 0)
	      {
		Block *block = new Block(1);
		block->setType(BLOCK);
		map[5][i].setObject(block);
		Block *block1 = new Block(1);
		block1->setType(BLOCK);
		map[5][x - 1 - i].setObject(block1);
		nbb = nbb - 2;
	      }
	  }
	else if (i >= (x * y / 4) + 1 && i < (x * y / 4) + 1 + y / 2 && map[i - (x * y / 4) + 1][6].getObject() == NULL)
	  {
	    i = i - (x * y / 4) + 1;
	    Block *block = new Block(1);
	    block->setType(BLOCK);
	    map[i][6].setObject(block);
	    Block *block1 = new Block(1);
	    block1->setType(BLOCK);
	    map[y - 1 - i][6].setObject(block1);
	    nbb = nbb - 2;
	  }
	else if (map[5][6].getObject() == NULL)
	  {
	    Block *block1 = new Block(1);
	    block1->setType(BLOCK);
	    map[5][6].setObject(block1);
	    nbb = nbb - 1;
	  }
      }
    nbb = 10;
    while (nbb > 0)
      {
	i = rand() % 99;
	if (map[i / x][i % x].getObject() && map[i / x][i % x].getObject()->getType() == BLOCK && dynamic_cast<Block *>(map[i / x][i % x].getObject())->getSolid() == false && dynamic_cast<Block *>(map[i / x][i % x].getObject())->getBonus() == NULL)
	  {
	    randbonus = (rand() * rand()) % 3;
	    Bonus       *bonus;
	    if (randbonus == 0)
	      bonus = new Bonus(BOMBUP);
	    else if (randbonus == 1)
	      bonus = new Bonus(FLAME);
	    else
	      bonus = new Bonus(BOOTS);
	    bonus->setType(BONUS);
	    Block *block = dynamic_cast<Block *>(map[i / x][i % x].getObject());
	    block->setBonus(bonus);
	    nbb = nbb - 1;
	  }
      }
    startTime = device->getTimer()->getRealTime();
    device->getCursorControl()->setVisible(false);
}



/*
** 	Step 3: ANIMATE
** 	everything which need to move (= be recalculated) at each frame.
*/

void 	Gameplay::animate(void) {
	
  if (this->getCharacters().size() > 0 && this->getCharacters()[0]->getAlive())
    {
      if (this->eventReceiver->IsKeyDown(KEY_KEY_Z))
	this->getCharacters()[0]->goUp();
      else if (this->eventReceiver->IsKeyDown(KEY_KEY_S))
        this->getCharacters()[0]->goDown();
      
      if (this->eventReceiver->IsKeyDown(KEY_KEY_Q))
        this->getCharacters()[0]->goLeft();
      else if (this->eventReceiver->IsKeyDown(KEY_KEY_D))
	this->getCharacters()[0]->goRight();
      
      if (this->eventReceiver->IsKeyDown(KEY_KEY_A) && this->characters[0]->getBombs().size() < this->characters[0]->getMaxBombs())
	this->getCharacters()[0]->bombing();
    }
  if (this->getCharacters().size() > 1 && this->getCharacters()[1]->getAlive())
    {
      if (this->eventReceiver->IsKeyDown(KEY_UP))
        this->getCharacters()[1]->goUp();
      else if (this->eventReceiver->IsKeyDown(KEY_DOWN))
        this->getCharacters()[1]->goDown();

      if (this->eventReceiver->IsKeyDown(KEY_LEFT))
        this->getCharacters()[1]->goLeft();
      else if (this->eventReceiver->IsKeyDown(KEY_RIGHT))
        this->getCharacters()[1]->goRight();

      if (this->eventReceiver->IsKeyDown(KEY_KEY_M) && this->characters[1]->getBombs().size() < this->characters[1]->getMaxBombs())
        this->getCharacters()[1]->bombing();
    }
  if (this->getCharacters().size() > 2 && this->getCharacters()[2]->getAlive())
    {
      if (this->eventReceiver->IsKeyDown(KEY_KEY_H))
        this->getCharacters()[2]->goUp();
      else if (this->eventReceiver->IsKeyDown(KEY_KEY_B))
        this->getCharacters()[2]->goDown();

      if (this->eventReceiver->IsKeyDown(KEY_KEY_V))
        this->getCharacters()[2]->goLeft();
      else if (this->eventReceiver->IsKeyDown(KEY_KEY_N))
        this->getCharacters()[2]->goRight();

      if (this->eventReceiver->IsKeyDown(KEY_KEY_C) && this->characters[2]->getBombs().size() < this->characters[2]->getMaxBombs())
        this->getCharacters()[2]->bombing();
    }
  if (this->getCharacters().size() > 3 && this->getCharacters()[3]->getAlive())
    {
      if (this->eventReceiver->IsKeyDown(KEY_KEY_I))
        this->getCharacters()[3]->goUp();
      else if (this->eventReceiver->IsKeyDown(KEY_KEY_K))
        this->getCharacters()[3]->goDown();

      if (this->eventReceiver->IsKeyDown(KEY_KEY_J))
        this->getCharacters()[3]->goLeft();
      else if (this->eventReceiver->IsKeyDown(KEY_KEY_L))
        this->getCharacters()[3]->goRight();

      if (this->eventReceiver->IsKeyDown(KEY_KEY_U) && this->characters[3]->getBombs().size() < this->characters[3]->getMaxBombs())
        this->getCharacters()[3]->bombing();
    }
}

/*
** 	Step 4: RENDER
** 	Call every methods needed to display the scene (sceneManager and/or gui).
*/

void 	Gameplay::render(void) {  
  this->driver->beginScene(true, true, video::SColor(0,200,200,200));
  this->drawBackground();
  this->majPosMesh();
  this->sceneManager->drawAll();
  this->drawObject();
  this->driver->endScene();
  if (this->isDraw == false)
    this->isDraw = true;
  if (this->isDrawChar == false)
    this->isDrawChar = true;
}
