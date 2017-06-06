#ifndef __NEWHIGHSCORE_HPP__
# define __NEWHIGHSCORE_HPP__

# include <fstream>

# include "GameManager.hpp"
# include "Gameplay.hpp"
# include "IScene.hpp"


struct SAppContextNewSco {
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

enum
{
    GUI_ID_CONFIRM_BUTTON = 101,
};

class NewScoEventReceiver : public IEventReceiver
{
public:
    NewScoEventReceiver(SAppContextNewSco & context, IrrlichtDevice *_device, std::stack<IScene *> *_scenesStack, bool *_stop, IGUIEditBox *_input, vector<int> _score, vector<std::string> _pseudo, int _id, fstream *_file) 
    : Context(context), device(_device), scenesStack(_scenesStack), stop(_stop), input(_input), score(_score), pseudo(_pseudo), pseudoid(_id) { }

    int     cptSpace(std::string s) {

        int cpt = 0;

        for (int i; i < s.size() ; i++) {
            if (s[i] == ' ')
                cpt++;
            }
        return (cpt);
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
                
                case GUI_ID_CONFIRM_BUTTON: {

                    if (!newpseudo.empty() && (cptSpace(newpseudo) == 0)) {

                        for (int i = 0; i < 5; i++) {
                            std::string s;
                            if (pseudoid != i)
                                s = pseudo[i] + " ";
                            else
                                s = newpseudo + " ";
                            s += to_string(score[i]);
                            *(file) << s << endl;
                        }

                        *(stop) = true;
                        file->close();
                        }
                    }
                    return true;


                default:
                    return false;
                }
                break;

            case EGET_EDITBOX_CHANGED: {
                const wchar_t* tmp = input->getText();
                wstring ws(tmp);
                std::string str(ws.begin(), ws.end());
                newpseudo = str;
                return true;
                }

            default:
                break;
            }
        }

        return false;
    }

private:
    SAppContextNewSco       &Context;
    IrrlichtDevice          *device;
    std::stack<IScene *>    *scenesStack;
    bool                    *stop;
    std::string             newpseudo;
    IGUIEditBox             *input;
    int                     pseudoid;
    vector<std::string>     pseudo;
    vector<int>             score;
    fstream                *file;
};

class NewHighScore : public IScene {

public:
	NewHighScore(IrrlichtDevice *, std::stack<IScene *> *, int);
	~NewHighScore();

	// Herited from IScene

	void 			init(int *);
	void 			render(void);
	void 			animate(void);

	IrrlichtDevice 	*getDevice(void);
	ISceneManager	*getSceneManager(void);
	IGUIEnvironment	*getGUIEnv(void);
	IVideoDriver	*getDriver(void);
    NewScoEventReceiver *getEventReceiver(void);

	void 			setDevice(IrrlichtDevice *);
	void 			setSceneManager(ISceneManager *);
	void 			setGUIEnv(IGUIEnvironment *);
	void 			setDriver(IVideoDriver *);
    void            setEventReceiver(NewScoEventReceiver *);

	// Member methods

private:
	// Herited from IScene

	IrrlichtDevice 			*device;
	ISceneManager			*sceneManager;
	IGUIEnvironment			*guiEnv;
	IVideoDriver 			*driver;
	std::stack<IScene *> 	*scenesStack;

	// Member variables

    NewScoEventReceiver        *eventReceiver;
    bool                    stop;
    fstream                file;
    int                     newscore;
};

#endif

