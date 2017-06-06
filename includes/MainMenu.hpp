#ifndef __MAINMENU_HPP__
# define __MAINMENU_HPP__

# include "GameManager.hpp"
# include "Gameplay.hpp"
# include "OptionsMenu.hpp"
# include "ScoreMenu.hpp"
# include "CreateGame.hpp"
# include "IScene.hpp"

struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

enum
{
    GUI_ID_PLAY_BUTTON = 101,
    GUI_ID_SCORE_BUTTON,
    GUI_ID_OPTIONS_BUTTON,
    GUI_ID_QUIT_BUTTON
};

class MyEventReceiver : public IEventReceiver
{
public:
    MyEventReceiver(SAppContext & context, IrrlichtDevice *_device,  std::stack<IScene *> *_scenesStack) 
    : Context(context), device(_device), scenesStack(_scenesStack) { }

    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType) {

            case EGET_BUTTON_CLICKED:
                switch(id) {
                
                case GUI_ID_PLAY_BUTTON: {
                    CreateGame *creategame = new CreateGame(this->device, this->scenesStack);
                    scenesStack->push(creategame);
                    }
                    return true;

                case GUI_ID_SCORE_BUTTON: {
                    ScoreMenu *score = new ScoreMenu(this->device, this->scenesStack);
                    scenesStack->push(score);
                    }
                    return true;

                case GUI_ID_OPTIONS_BUTTON: {
                    OptionsMenu *options = new OptionsMenu(this->device,  this->scenesStack);
                    scenesStack->push(options);
                    }
                    return true;            

                case GUI_ID_QUIT_BUTTON:
                    Context.device->closeDevice();
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
    SAppContext             &Context;
    IrrlichtDevice          *device;
    std::stack<IScene *>    *scenesStack;
};

class MainMenu : public IScene {

public:
	MainMenu(IrrlichtDevice *, std::stack<IScene *> *);
	~MainMenu();

	// Herited from IScene

	void 			init(int *);
	void 			render(void);
	void 			animate(void);

	IrrlichtDevice 	*getDevice(void);
	ISceneManager	*getSceneManager(void);
	IGUIEnvironment	*getGUIEnv(void);
	IVideoDriver	*getDriver(void);
    MyEventReceiver *getEventReceiver(void);

	void 			setDevice(IrrlichtDevice *);
	void 			setSceneManager(ISceneManager *);
	void 			setGUIEnv(IGUIEnvironment *);
	void 			setDriver(IVideoDriver *);
    void            setEventReceiver(MyEventReceiver *);

	// Member methods

private:
	// Herited from IScene

	IrrlichtDevice 			*device;
	ISceneManager			*sceneManager;
	IGUIEnvironment			*guiEnv;
	IVideoDriver 			*driver;
	std::stack<IScene *> 	*scenesStack;

	// Member variables

    MyEventReceiver         *eventReceiver;
    ITexture                *banner;
    ITexture                *background;
    SColor                  empty_color;

};

#endif

