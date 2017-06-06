#include "MainMenu.hpp"

/*
**	Main menu. 
**	Scene description: At the bottom of the stack. Displayed after the splashscreen.
*/

/*
    Set the skin transparency by changing the alpha values of all skin-colors
*/

MainMenu::MainMenu(IrrlichtDevice *device, std::stack<IScene *> *stack) { 
	this->device = device;
	this->sceneManager = this->device->getSceneManager();
	this->guiEnv = this->device->getGUIEnvironment();
	this->driver = this->device->getVideoDriver();
	this->scenesStack = stack;
}

MainMenu::~MainMenu() { }

IrrlichtDevice  *MainMenu::getDevice(void) { return (this->device); }
ISceneManager	*MainMenu::getSceneManager(void) { return (this->sceneManager); }
IGUIEnvironment	*MainMenu::getGUIEnv(void) { return (this->guiEnv); }
IVideoDriver	*MainMenu::getDriver(void) { return (this->driver); }
MyEventReceiver  *MainMenu::getEventReceiver(void) { return (this->eventReceiver); }

void            MainMenu::setDevice(IrrlichtDevice *arg) { this->device = arg; }
void 			MainMenu::setSceneManager(ISceneManager *arg) { this->sceneManager = arg; }
void 			MainMenu::setGUIEnv(IGUIEnvironment *arg) { this->guiEnv = arg; }
void 			MainMenu::setDriver(IVideoDriver *arg) { this->driver = arg; }
void            MainMenu::setEventReceiver(MyEventReceiver *arg) { this->eventReceiver = arg; }



/* 
** Step 2: INITIALIZATION
** Everything which need to be calculated only at the beginning of the scene.
** For example cameras, models, textures...
*/

void 	MainMenu::init(int *mapID) {

    this->sceneManager->clear();
    this->guiEnv->clear();

    IGUISkin    *skin = guiEnv->getSkin();
    IGUIFont    *font = guiEnv->getFont("./assets/fonts/saber.png");

    if (font)
        skin->setFont(font);

    skin->setFont(guiEnv->getBuiltInFont(), EGDF_TOOLTIP);

    //    if (music_loop == NULL)
    //  this->music_loop = this->soundEngine->play2D("./assets/audio/music/mainmenu.ogg", true, false, true);

    banner = driver->getTexture("./assets/images/banner.png");
    background = driver->getTexture("./assets/images/background.jpg");

    driver->makeColorKeyTexture(banner, position2d<s32> (0,0));
    empty_color.set(255, 255, 255, 255);

    guiEnv->addButton(rect<s32>(MID_WIDTH - 250, MID_HEIGHT - 100, MID_WIDTH + 250, MID_HEIGHT - 10), 0, GUI_ID_PLAY_BUTTON, L"PLAY", L"Create a game");
    guiEnv->addButton(rect<s32>(MID_WIDTH - 250, MID_HEIGHT, MID_WIDTH + 250, MID_HEIGHT + 90), 0, GUI_ID_SCORE_BUTTON, L"SCORE", L"Check your ranking");
    guiEnv->addButton(rect<s32>(MID_WIDTH - 250, MID_HEIGHT + 100, MID_WIDTH + 250, MID_HEIGHT + 190), 0, GUI_ID_OPTIONS_BUTTON, L"OPTIONS", L"Change your settings");
    guiEnv->addButton(rect<s32>(MID_WIDTH - 250, MID_HEIGHT + 200, MID_WIDTH + 250, MID_HEIGHT + 290), 0, GUI_ID_QUIT_BUTTON, L"QUIT", L"Exit the game");


    SAppContext *context = new SAppContext;
    if (context) {
       context->device = this->getDevice();
        context->counter = 0;
    }
    else
        throw std::string(strerror(ENOMEM));

    this->eventReceiver = new MyEventReceiver(*context, device, scenesStack);

    if (this->eventReceiver)
        device->setEventReceiver(this->eventReceiver);
    else
        throw std::string(strerror(ENOMEM));
}



/*
** 	Step 3: ANIMATE
** 	everything which need to move (= be recalculated) at each frame.
*/

void 	MainMenu::animate(void) {
	
}



/*
** 	Step 4: RENDER
** 	Call every methods needed to display the scene (sceneManager and/or gui).
*/

void 	MainMenu::render(void) {

	this->driver->beginScene(true, true, video::SColor(0,255,255,255));
    driver->draw2DImage(background, position2d<s32> (0, 0), rect<s32> (0,0,1280,720), 0, empty_color, true);
	this->guiEnv->drawAll();
    driver->draw2DImage(banner, position2d<s32> (MID_WIDTH - 200, 30), rect<s32> (0,0,400,169), 0, empty_color, true);
    this->driver->endScene();
}
