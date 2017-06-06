#include "ScoreMenu.hpp"

/*
**	Main menu. 
**	Scene description: At the bottom of the stack. Displayed after the splashscreen.
*/

/*
    Set the skin transparency by changing the alpha values of all skin-colors
*/

ScoreMenu::ScoreMenu(IrrlichtDevice *device, std::stack<IScene *> *stack) { 
	this->device = device;
	this->sceneManager = this->device->getSceneManager();
	this->guiEnv = this->device->getGUIEnvironment();
	this->driver = this->device->getVideoDriver();
	this->scenesStack = stack;
	this->stop = false;
}

ScoreMenu::~ScoreMenu() { }

IrrlichtDevice  *ScoreMenu::getDevice(void) { return (this->device); }
ISceneManager	*ScoreMenu::getSceneManager(void) { return (this->sceneManager); }
IGUIEnvironment	*ScoreMenu::getGUIEnv(void) { return (this->guiEnv); }
IVideoDriver	*ScoreMenu::getDriver(void) { return (this->driver); }
ScoEventReceiver  *ScoreMenu::getEventReceiver(void) { return (this->eventReceiver); }

void            ScoreMenu::setDevice(IrrlichtDevice *arg) { this->device = arg; }
void 			ScoreMenu::setSceneManager(ISceneManager *arg) { this->sceneManager = arg; }
void 			ScoreMenu::setGUIEnv(IGUIEnvironment *arg) { this->guiEnv = arg; }
void 			ScoreMenu::setDriver(IVideoDriver *arg) { this->driver = arg; }
void            ScoreMenu::setEventReceiver(ScoEventReceiver *arg) { this->eventReceiver = arg; }



/* 
** Step 2: INITIALIZATION
** Everything which need to be calculated only at the beginning of the scene.
** For example cameras, models, textures...
*/

void 	ScoreMenu::init(int *) {

    this->sceneManager->clear();
    this->guiEnv->clear();

    IGUISkin    *skin = guiEnv->getSkin();
    IGUIFont    *font = guiEnv->getFont("./assets/fonts/saber.png");

    if (font)
        skin->setFont(font);

    skin->setFont(guiEnv->getBuiltInFont(), EGDF_TOOLTIP);

    this->file.open("scores");

    if (!file.is_open())
        throw std::string(ERR_SCO_CANTLOAD);

    std::string     pseudo, score;
    IGUIStaticText      *tmp;
    int     i = 1;

    // On lis le fichier score
    while (file >> pseudo >> score) {
        std::string s = "#" + to_string(i) + "\t" + pseudo;
        tmp = guiEnv->addStaticText(getStringw(s).c_str(), rect<s32>(MID_WIDTH - 250, MID_HEIGHT - 350 + (i * 80), MID_WIDTH + 107, MID_HEIGHT - 295 + (i * 80)), true);
        tmp->setTextAlignment(EGUIA_SCALE, EGUIA_SCALE);
        tmp = guiEnv->addStaticText(getStringw(score).c_str(), rect<s32>(MID_WIDTH + 130, MID_HEIGHT - 350 + (i * 80), MID_WIDTH + 250, MID_HEIGHT - 295 + (i * 80)), true);
        tmp->setTextAlignment(EGUIA_LOWERRIGHT, EGUIA_SCALE);
        i++;
   }
   
    guiEnv->addButton(rect<s32>(MID_WIDTH - 250, MID_HEIGHT + 200, MID_WIDTH + 250, MID_HEIGHT + 290), 0, GUI_ID_QUIT_BUTTON_SCO, L"BACK", L"Back to main menu");

    SAppContextSco *context = new SAppContextSco;
    if (context) {
       context->device = this->getDevice();
       context->counter = 0;
    } else
        throw std::string(strerror(ENOMEM));

    this->eventReceiver = new ScoEventReceiver(*context, this->device, this->scenesStack, &this->stop);

    if (this->eventReceiver)
        device->setEventReceiver(this->eventReceiver);
    else
        throw std::string(strerror(ENOMEM));
}



/*
** 	Step 3: ANIMATE
** 	everything which need to move (= be recalculated) at each frame.
*/

void 	ScoreMenu::animate(void) {
	
}



/*
** 	Step 4: RENDER
** 	Call every methods needed to display the scene (sceneManager and/or gui).
*/


void 	ScoreMenu::render(void) {

	this->driver->beginScene(true, true, video::SColor(0,133,133,133));
	this->guiEnv->drawAll();
	this->driver->endScene();

    if (this->stop) {
        delete scenesStack->top();
        scenesStack->pop();
    }
}
