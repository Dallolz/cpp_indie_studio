#include "OptionsMenu.hpp"

/*
**	Main menu. 
**	Scene description: At the bottom of the stack. Displayed after the splashscreen.
*/

/*
    Set the skin transparency by changing the alpha values of all skin-colors
*/

OptionsMenu::OptionsMenu(IrrlichtDevice *device, ISoundEngine *sound, std::stack<IScene *> *stack) { 
	this->device = device;
    this->soundEngine = sound;
    this->sceneManager = this->device->getSceneManager();
	this->guiEnv = this->device->getGUIEnvironment();
	this->driver = this->device->getVideoDriver();
	this->scenesStack = stack;
    this->stop = false;
}

OptionsMenu::~OptionsMenu() { }

IrrlichtDevice  *OptionsMenu::getDevice(void) { return (this->device); }
ISceneManager	*OptionsMenu::getSceneManager(void) { return (this->sceneManager); }
IGUIEnvironment	*OptionsMenu::getGUIEnv(void) { return (this->guiEnv); }
IVideoDriver	*OptionsMenu::getDriver(void) { return (this->driver); }
ISoundEngine    *OptionsMenu::getSoundEngine(void) { return (this->soundEngine); }
OptEventReceiver  *OptionsMenu::getEventReceiver(void) { return (this->eventReceiver); }

void            OptionsMenu::setDevice(IrrlichtDevice *arg) { this->device = arg; }
void 			OptionsMenu::setSceneManager(ISceneManager *arg) { this->sceneManager = arg; }
void 			OptionsMenu::setGUIEnv(IGUIEnvironment *arg) { this->guiEnv = arg; }
void 			OptionsMenu::setDriver(IVideoDriver *arg) { this->driver = arg; }
void            OptionsMenu::setSoundEngine(ISoundEngine *arg) { this->soundEngine = arg; }
void            OptionsMenu::setEventReceiver(OptEventReceiver *arg) { this->eventReceiver = arg; }



/* 
** Step 2: INITIALIZATION
** Everything which need to be calculated only at the beginning of the scene.
** For example cameras, models, textures...
*/

void 	OptionsMenu::init(int *mapID) {

    this->sceneManager->clear();
    this->guiEnv->clear();

    IGUISkin    *skin = guiEnv->getSkin();
    IGUIFont    *font = guiEnv->getFont("./assets/fonts/saber.png");

    if (font)
        skin->setFont(font);

    skin->setFont(guiEnv->getBuiltInFont(), EGDF_TOOLTIP);

    guiEnv->addStaticText(L"Music", rect<s32>(MID_WIDTH - 250, MID_HEIGHT - 300, MID_WIDTH - 150, MID_HEIGHT - 270), true);
    guiEnv->addStaticText(L"MAP", rect<s32>(MID_WIDTH - 250, MID_HEIGHT - 220, MID_WIDTH + 250, MID_HEIGHT - 190), true);
    IGUIScrollBar* scrollbar = guiEnv->addScrollBar(true, rect<s32>(MID_WIDTH - 130, MID_HEIGHT - 300, MID_WIDTH + 250, MID_HEIGHT - 280), 0, GUI_ID_MUSIC_VOLUME);
    scrollbar->setMax(100);
    scrollbar->setPos(soundEngine->getSoundVolume() * 100);

    guiEnv->addButton(rect<s32>(MID_WIDTH - 250, MID_HEIGHT + 200, MID_WIDTH + 250, MID_HEIGHT + 290), 0, GUI_ID_QUIT_BUTTON_OPT, L"BACK", L"Back to main menu");

    SAppContextOpt *context = new SAppContextOpt;

    if (context) {
        context->device = this->getDevice();
        context->counter = 0;
        context->listbox = guiEnv->addListBox(rect<s32>(MID_WIDTH - 250, MID_HEIGHT - 160, MID_WIDTH + 250, MID_HEIGHT + 80));
        context->listbox->addItem(L"Sky");
        context->listbox->addItem(L"Desert");
        context->listbox->addItem(L"Ocean");
        context->listbox->addItem(L"Volcano");
        context->listbox->setSelected(*mapID);
    } else
        throw std::string(strerror(ENOMEM));

    this->eventReceiver = new OptEventReceiver(*context, this->device, this->soundEngine, this->scenesStack, &this->stop, mapID);

    if (this->eventReceiver)
        device->setEventReceiver(this->eventReceiver);
    else
        throw std::string(strerror(ENOMEM));
}



/*
** 	Step 3: ANIMATE
** 	everything which need to move (= be recalculated) at each frame.
*/

void 	OptionsMenu::animate(void) {
	
}



/*
** 	Step 4: RENDER
** 	Call every methods needed to display the scene (sceneManager and/or gui).
*/


void 	OptionsMenu::render(void) {

	this->driver->beginScene(true, true, video::SColor(0,133,133,133));
	this->guiEnv->drawAll();
	this->driver->endScene();

    if (this->stop) {
        delete scenesStack->top();
        scenesStack->pop();
    }
}
