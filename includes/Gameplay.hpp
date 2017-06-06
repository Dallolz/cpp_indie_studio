#ifndef __GAMEPLAY_HPP__
# define __GAMEPLAY_HPP__

# include <vector>
# include "Square.hh"
# include "Character.hh"
# include "GameManager.hpp"
# include "NewHighScore.hpp"
# include "IScene.hpp"
# include "Game.hh"
# include "Bonus.hh"
# include "Object.hh"
# include "irrlicht.h"

class GEventReceiver : public IEventReceiver {

public:

	GEventReceiver() {
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

	virtual bool OnEvent(const SEvent& event) {

		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		  {
		    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		    return (true);
		  }

		return (false);
	}

	virtual bool IsKeyDown(EKEY_CODE keyCode) {
		return (KeyIsDown[keyCode]);
	}
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

class Gameplay : public IScene {

public:
  Gameplay(IrrlichtDevice *, std::stack<IScene *> *);
  ~Gameplay();
  
  // Herited from IScene
  
  void 			init(int *);
  void 			render(void);
  void 			animate(void);
  
  IrrlichtDevice 	*getDevice(void);
  ISceneManager		*getSceneManager(void);
  IGUIEnvironment	*getGUIEnv(void);
  IVideoDriver		*getDriver(void);
  GEventReceiver	*getEventReceiver(void);
  
  
  void 			setDevice(IrrlichtDevice *);
  void 			setSceneManager(ISceneManager *);
  void 			setGUIEnv(IGUIEnvironment *);
  void 			setDriver(IVideoDriver *);
  void 			setEventReceiver(GEventReceiver *);
  
  // Member methods
  
  void 	setBGMusic(int);
  int   getX() const;
  int   getY() const;
  std::vector<std::vector<Square> > const       &getMap() const;
  std::vector<Character *> const        &getCharacters() const;
  void  setCharacters(std::vector<Character *> *);
  void  addCharacter(Character *character);
  void  affMapOnConsole();
  void  majPosMesh();
  void  explode(Bomb *bomb);
  irr::u32	getTime() const;
  bool  isNewHighScore(int) const;

  // Draw

  void	drawObject();
  void  drawChar4(float x, float z);
  void  drawChar3(float x, float z);
  void	drawChar2(float x, float z);
  void	drawChar1(float x, float z);
  void  drawBackground(void);

private:
  // Herited from IScene
  
  IrrlichtDevice 		*device;
  ISceneManager			*sceneManager;
  IGUIEnvironment		*guiEnv;
  IVideoDriver 			*driver;
  std::stack<IScene *>		*scenesStack;
  
  // Member variables
  
  GEventReceiver         *eventReceiver;
  std::vector<std::vector<Square> >     map;
  std::vector<std::vector<irr::scene::ISceneNode *>>	mapDraw;
  std::vector<Character *>      characters;
  int   x;
  int   y;
  irr::u32	startTime;

  // Character for draw
  irr::scene::IAnimatedMeshSceneNode * Char1;
  irr::scene::IAnimatedMeshSceneNode * Char2;
  irr::scene::IAnimatedMeshSceneNode * Char3;
  irr::scene::IAnimatedMeshSceneNode * Char4;
  irr::scene::ISceneNode * Structure;
  irr::scene::ISceneNode * Bonus_irr;
  irr::scene::ISceneNode * Bombe;
  
  bool	isDraw;
  bool	isDrawChar;
  bool	char1Animation;
  bool	char2Animation;
  bool  char3Animation;
  bool  char4Animation;

  io::path                background;
};

#endif
