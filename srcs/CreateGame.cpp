#include "CreateGame.hpp"

/*
**	Main menu. 
**	Scene description: At the bottom of the stack. Displayed after the splashscreen.
*/

/*
    Set the skin transparency by changing the alpha values of all skin-colors
*/

CreateGame::CreateGame(IrrlichtDevice *device, ISoundEngine *sound, std::stack<IScene *> *stack) { 
	this->device = device;
    this->soundEngine = sound;
    this->sceneManager = this->device->getSceneManager();
	this->guiEnv = this->device->getGUIEnvironment();
	this->driver = this->device->getVideoDriver();
	this->scenesStack = stack;
    this->stop = false;
}

CreateGame::~CreateGame() { }

IrrlichtDevice  *CreateGame::getDevice(void) { return (this->device); }
ISceneManager	*CreateGame::getSceneManager(void) { return (this->sceneManager); }
IGUIEnvironment	*CreateGame::getGUIEnv(void) { return (this->guiEnv); }
IVideoDriver	*CreateGame::getDriver(void) { return (this->driver); }
ISoundEngine    *CreateGame::getSoundEngine(void) { return (this->soundEngine); }
CGEventReceiver  *CreateGame::getEventReceiver(void) { return (this->eventReceiver); }

void            CreateGame::setDevice(IrrlichtDevice *arg) { this->device = arg; }
void 			CreateGame::setSceneManager(ISceneManager *arg) { this->sceneManager = arg; }
void 			CreateGame::setGUIEnv(IGUIEnvironment *arg) { this->guiEnv = arg; }
void 			CreateGame::setDriver(IVideoDriver *arg) { this->driver = arg; }
void            CreateGame::setSoundEngine(ISoundEngine *arg) { this->soundEngine = arg; }
void            CreateGame::setEventReceiver(CGEventReceiver *arg) { this->eventReceiver = arg; }



/* 
** Step 2: INITIALIZATION
** Everything which need to be calculated only at the beginning of the scene.
** For example cameras, models, textures...
*/

void 	CreateGame::init(int *mapID) {

    this->sceneManager->clear();
    this->guiEnv->clear();

    IGUISkin    *skin = guiEnv->getSkin();
    IGUIFont    *font = guiEnv->getFont("./assets/fonts/saber.png");

    guiEnv->addButton(rect<s32>(MID_WIDTH - 250, MID_HEIGHT - 300, MID_WIDTH - 20, MID_HEIGHT - 230), 0, GUI_ID_ADDPLAYER_BUTTON, L"PLAYER", L"Add a player");
    guiEnv->addButton(rect<s32>(MID_WIDTH + 20, MID_HEIGHT - 300, MID_WIDTH + 250, MID_HEIGHT - 230), 0, GUI_ID_ADDBOT_BUTTON, L"BOT", L"Add a bot");
    guiEnv->addButton(rect<s32>(MID_WIDTH - 250, MID_HEIGHT + 200, MID_WIDTH - 20, MID_HEIGHT + 290), 0, GUI_ID_QUIT_BUTTON_CG, L"BACK", L"Back to main menu");
    guiEnv->addButton(rect<s32>(MID_WIDTH + 20, MID_HEIGHT + 200, MID_WIDTH + 250, MID_HEIGHT + 290), 0, GUI_ID_PLAYBUTTON_CG, L"START", L"Launch a game");

    if (font)
        skin->setFont(font);

    skin->setFont(guiEnv->getBuiltInFont(), EGDF_TOOLTIP);

    SAppContextCG *context = new SAppContextCG;
    if (context) {
       context->device = this->getDevice();
       context->counter = 0;
       context->listbox = guiEnv->addListBox(rect<s32>(MID_WIDTH - 250, MID_HEIGHT - 200, MID_WIDTH + 250, MID_HEIGHT + 40));
    } else
        throw std::string(strerror(ENOMEM));

    Gameplay *gameplay = new Gameplay(this->device, this->soundEngine, this->scenesStack);

    this->eventReceiver = new CGEventReceiver(*context, this->device, this->soundEngine, this->scenesStack, &this->stop, &this->charList, gameplay);

    if (this->eventReceiver)
        device->setEventReceiver(this->eventReceiver);
    else
        throw std::string(strerror(ENOMEM));
}



/*
** 	Step 3: ANIMATE
** 	everything which need to move (= be recalculated) at each frame.
*/

void 	CreateGame::animate(void) {
	
}



/*
** 	Step 4: RENDER
** 	Call every methods needed to display the scene (sceneManager and/or gui).
*/


void 	CreateGame::render(void) {

	this->driver->beginScene(true, true, video::SColor(0,133,133,133));
	this->guiEnv->drawAll();
	this->driver->endScene();

    if (this->stop) {
        delete scenesStack->top();
        scenesStack->pop();
    }
}
