#ifndef __OPTIONSMENU_HPP__
# define __OPTIONSMENU_HPP__

# include "GameManager.hpp"
# include "Gameplay.hpp"
# include "IScene.hpp"

struct SAppContextOpt {
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

enum
{
    GUI_ID_QUIT_BUTTON_OPT = 101,
    GUI_ID_MUSIC_VOLUME
};

class OptEventReceiver : public IEventReceiver
{
public:
    OptEventReceiver(SAppContextOpt & context, IrrlichtDevice *_device,  std::stack<IScene *> *_scenesStack, bool *_stop, int *_mapID) 
    : Context(context), device(_device), scenesStack(_scenesStack), stop(_stop), mapID(_mapID) { }

    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType) {

            case EGET_BUTTON_CLICKED:
                switch(id) {
                
                case GUI_ID_QUIT_BUTTON_OPT:
                    *(stop) = true;
                    return true;

                default:
                    return false;
                }
                break;

            case EGET_SCROLL_BAR_CHANGED:
                if (id == GUI_ID_MUSIC_VOLUME)
                {
                    s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                    float volume = (float)pos / (float)100;
                }
                break;

            case EGET_LISTBOX_CHANGED: {
                    *mapID = Context.listbox->getSelected();
                }
                return true; 

            default:
                break;
            }
        }

        return false;
    }

private:
    SAppContextOpt          &Context;
    IrrlichtDevice          *device;
    std::stack<IScene *>    *scenesStack;
    bool                    *stop;
    int                     *mapID;
};

class OptionsMenu : public IScene {

public:
	OptionsMenu(IrrlichtDevice *, std::stack<IScene *> *);
	~OptionsMenu();

	// Herited from IScene

	void 			init(int *m);
	void 			render(void);
	void 			animate(void);

	IrrlichtDevice 	*getDevice(void);
	ISceneManager	*getSceneManager(void);
	IGUIEnvironment	*getGUIEnv(void);
	IVideoDriver	*getDriver(void);
    OptEventReceiver *getEventReceiver(void);

	void 			setDevice(IrrlichtDevice *);
	void 			setSceneManager(ISceneManager *);
	void 			setGUIEnv(IGUIEnvironment *);
	void 			setDriver(IVideoDriver *);
    void            setEventReceiver(OptEventReceiver *);

	// Member methods

private:
	// Herited from IScene

	IrrlichtDevice 			*device;
	ISceneManager			*sceneManager;
	IGUIEnvironment			*guiEnv;
	IVideoDriver 			*driver;
	std::stack<IScene *> 	*scenesStack;

	// Member variables

    OptEventReceiver        *eventReceiver;
    bool                    stop;
    int                     *mapID;
};

#endif

