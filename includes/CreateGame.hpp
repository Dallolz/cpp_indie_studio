#ifndef __CREATEGAME_HPP__
# define __CREATEGAME_HPP__

# include "GameManager.hpp"
# include "Gameplay.hpp"
# include "IScene.hpp"

struct SAppContextCG {
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

enum
{
    GUI_ID_QUIT_BUTTON_CG = 101,
    GUI_ID_ADDPLAYER_BUTTON,
    GUI_ID_ADDBOT_BUTTON,
    GUI_ID_PLAYBUTTON_CG
};

class CGEventReceiver : public IEventReceiver
{
public:
    CGEventReceiver(SAppContextCG & context, IrrlichtDevice *_device, std::stack<IScene *> *_scenesStack, bool *_stop, vector<Character *> *_charList, Gameplay *_gameplay) 
    : Context(context), device(_device), scenesStack(_scenesStack), stop(_stop), charList(_charList), gameplay(_gameplay) { }

    int         countBot() {
        int     i = 0;

        for (int j = 0; j < charList->size() ; j++) {
            if ((*charList)[j]->getType() == BOT)
                i++;
        }
        return (i + 1);
    }

    int        countPlayer() {
        int    i = 0; 
        
        for (int j = 0; j < charList->size() ; j++) {
            if ((*charList)[j]->getType() == PLAYER)
                i++;
        }
        return (i + 1);
    }

    long createRGB(int r, int g, int b) {   
        return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
    }

    long         defaultColor(int i) {
        long col[] = {  createRGB(0x00, 0x00, 0xFF), 
                        createRGB(0xFF, 0x00, 0x00), 
                        createRGB(0x00, 0xFF, 0x00), 
                        createRGB(0xFF, 0xFF, 0x00) };
        return (col[i]);
    }

    int         posX(int i) {
        int x[] = { 5, 125, 5, 125 };
        return (x[i]);
    }

    int         posY(int i) {
        int y[] = { 5, 5, 105, 105 };
        return (y[i]);
    }

    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType) {

            case EGET_BUTTON_CLICKED:
                switch(id) {
                
                case GUI_ID_QUIT_BUTTON_CG:
                    *(stop) = true;
                    return true;

                case GUI_ID_ADDPLAYER_BUTTON: {
                    if (charList->size() < 4) {
                        Character *charac = new Character(defaultColor(charList->size()), posX(charList->size()), posY(charList->size()), &gameplay->getMap(), device, PLAYER);
                        std::string s = "PLAYER " + to_string(countPlayer());
                        Context.listbox->addItem(getStringw(s).c_str());
                        charList->push_back(charac);
                        }
                    }
                    return true;

                case GUI_ID_ADDBOT_BUTTON: {
                    if (charList->size() < 4) {
                        Character *charac = new Character(defaultColor(charList->size()), posX(charList->size()), posY(charList->size()), &gameplay->getMap(), device, BOT);
                        std::string s = "BOT " + to_string(countBot());
                        Context.listbox->addItem(getStringw(s).c_str());
                        charList->push_back(charac);
                        }
                    }
                    return true;

                case GUI_ID_PLAYBUTTON_CG: {
                    if (charList->size() >= 2) {
                         gameplay->setCharacters(charList);
                         scenesStack->push(gameplay);
                        }
                    }
                    return true;

                default:
                    return false;
                }
                break;

            case EGET_LISTBOX_CHANGED: {
                    int index = charList->size() - 1;
                    charList->erase(charList->begin() + index);
                    Context.listbox->removeItem(index);

                }
                return true;

            default:
                break;
            }
        }

        return false;
    }

private:
    SAppContextCG           &Context;
    IrrlichtDevice          *device;
    std::stack<IScene *>    *scenesStack;
    bool                    *stop;
    vector<Character *>     *charList;
    Gameplay                *gameplay;

};

class CreateGame : public IScene {

public:
	CreateGame(IrrlichtDevice *, std::stack<IScene *> *);
	~CreateGame();

	// Herited from IScene

	void 			init(int *);
	void 			render(void);
	void 			animate(void);

	IrrlichtDevice 	*getDevice(void);
	ISceneManager	*getSceneManager(void);
	IGUIEnvironment	*getGUIEnv(void);
	IVideoDriver	*getDriver(void);
    CGEventReceiver *getEventReceiver(void);

	void 			setDevice(IrrlichtDevice *);
	void 			setSceneManager(ISceneManager *);
	void 			setGUIEnv(IGUIEnvironment *);
	void 			setDriver(IVideoDriver *);
    void            setEventReceiver(CGEventReceiver *);

	// Member methods

    void            printCharacter(int);

private:
	// Herited from IScene

	IrrlichtDevice 			*device;
	ISceneManager			*sceneManager;
	IGUIEnvironment			*guiEnv;
	IVideoDriver 			*driver;
	stack<IScene *> 	    *scenesStack;

	// Member variables

    CGEventReceiver        *eventReceiver;
    bool                    stop;
    vector<Character *>     charList;
};

#endif

