#ifndef __ISCENE_HPP__
# define __ISCENE_HPP__

# include "irrlicht.h"

class IScene {
public:
	IScene() {}
	IScene(IrrlichtDevice *, ISoundEngine *, std::stack<IScene *> *) {}
	virtual ~IScene() {}

	virtual void 			init(int *) = 0;
	virtual void 			animate() = 0;
	virtual void 			render() = 0;

	virtual IrrlichtDevice 	*getDevice(void) = 0;
	virtual ISceneManager	*getSceneManager(void) = 0;
	virtual IGUIEnvironment	*getGUIEnv(void) = 0;
	virtual IVideoDriver	*getDriver(void) = 0;
	virtual ISoundEngine	*getSoundEngine(void) = 0;

	virtual void 			setDevice(IrrlichtDevice *) = 0;
	virtual void 			setSceneManager(ISceneManager *) = 0;
	virtual void 			setGUIEnv(IGUIEnvironment *) = 0;
	virtual void 			setDriver(IVideoDriver *) = 0;
	virtual void 			setSoundEngine(ISoundEngine	*) = 0;

private:
	IrrlichtDevice 			*device;
	ISceneManager			*sceneManager;
	IGUIEnvironment			*guiEnv;
	IVideoDriver 			*driver;
	ISoundEngine			*soundEngine;
	std::stack<IScene *> 	*scenesStack;
};

#endif