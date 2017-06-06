#ifndef __SCOREMENU_HPP__
# define __SCOREMENU_HPP__

# include <fstream>

# include "GameManager.hpp"
# include "Gameplay.hpp"
# include "IScene.hpp"


struct SAppContextSco {
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

enum
{
    GUI_ID_QUIT_BUTTON_SCO = 101,
};

class ScoEventReceiver : public IEventReceiver
{
public:
    ScoEventReceiver(SAppContextSco & context, IrrlichtDevice *_device, std::stack<IScene *> *_scenesStack, bool *_stop) 
    : Context(context), device(_device), scenesStack(_scenesStack), stop(_stop) { }

    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType) {

            case EGET_BUTTON_CLICKED:
                switch(id) {
                
                case GUI_ID_QUIT_BUTTON_SCO:
                    *(stop) = true;
                    return true;

                default:
                    return false;
                }
                break;

            default:
                break;
            }
        }

        return false;
    }

private:
    SAppContextSco          &Context;
    IrrlichtDevice          *device;
    std::stack<IScene *>    *scenesStack;
    bool                    *stop;
};

class ScoreMenu : public IScene {

public:
	ScoreMenu(IrrlichtDevice *, std::stack<IScene *> *);
	~ScoreMenu();

	// Herited from IScene

	void 			init(int *);
	void 			render(void);
	void 			animate(void);

	IrrlichtDevice 	*getDevice(void);
	ISceneManager	*getSceneManager(void);
	IGUIEnvironment	*getGUIEnv(void);
	IVideoDriver	*getDriver(void);
    ScoEventReceiver *getEventReceiver(void);

	void 			setDevice(IrrlichtDevice *);
	void 			setSceneManager(ISceneManager *);
	void 			setGUIEnv(IGUIEnvironment *);
	void 			setDriver(IVideoDriver *);
    void            setEventReceiver(ScoEventReceiver *);

	// Member methods

private:
	// Herited from IScene

	IrrlichtDevice 			*device;
	ISceneManager			*sceneManager;
	IGUIEnvironment			*guiEnv;
	IVideoDriver 			*driver;
	std::stack<IScene *> 	*scenesStack;

	// Member variables

    ScoEventReceiver        *eventReceiver;
    bool                    stop;
    ifstream                file;
};

#endif

