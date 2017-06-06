#include "NewHighScore.hpp"

/*
**	Main menu. 
**	Scene description: At the bottom of the stack. Displayed after the splashscreen.
*/

/*
    Set the skin transparency by changing the alpha values of all skin-colors
*/

NewHighScore::NewHighScore(IrrlichtDevice *device, std::stack<IScene *> *stack, int score) { 
	this->device = device;
	this->sceneManager = this->device->getSceneManager();
	this->guiEnv = this->device->getGUIEnvironment();
	this->driver = this->device->getVideoDriver();
	this->scenesStack = stack;
    this->stop = false;
    this->newscore = score;
}

NewHighScore::~NewHighScore() { }

IrrlichtDevice  *NewHighScore::getDevice(void) { return (this->device); }
ISceneManager	*NewHighScore::getSceneManager(void) { return (this->sceneManager); }
IGUIEnvironment	*NewHighScore::getGUIEnv(void) { return (this->guiEnv); }
IVideoDriver	*NewHighScore::getDriver(void) { return (this->driver); }
NewScoEventReceiver  *NewHighScore::getEventReceiver(void) { return (this->eventReceiver); }

void            NewHighScore::setDevice(IrrlichtDevice *arg) { this->device = arg; }
void 			NewHighScore::setSceneManager(ISceneManager *arg) { this->sceneManager = arg; }
void 			NewHighScore::setGUIEnv(IGUIEnvironment *arg) { this->guiEnv = arg; }
void 			NewHighScore::setDriver(IVideoDriver *arg) { this->driver = arg; }
void            NewHighScore::setEventReceiver(NewScoEventReceiver *arg) { this->eventReceiver = arg; }



/* 
** Step 2: INITIALIZATION
** Everything which need to be calculated only at the beginning of the scene.
** For example cameras, models, textures...
*/

void 	NewHighScore::init(int *) {

    this->sceneManager->clear();
    this->guiEnv->clear();


    IGUISkin    *skin = guiEnv->getSkin();
    IGUIFont    *font = guiEnv->getFont("./assets/fonts/saber.png");

    if (font)
        skin->setFont(font);


    skin->setFont(guiEnv->getBuiltInFont(), EGDF_TOOLTIP);

    // On lis le fichier score
    this->file.open("scores");

    if (!file.is_open())
        throw std::string(ERR_SCO_CANTLOAD);

    std::string             tmp_pseudo, tmp_score;
    vector<std::string>     pseudo;
    vector<int>             score;

    bool empty = ( file.get(), file.eof() );

    if (empty) {
        pseudo.push_back("Player");
        pseudo.push_back("Player");
        pseudo.push_back("Player");
        pseudo.push_back("Player");
        pseudo.push_back("Player");
        score.push_back(0);
        score.push_back(0);
        score.push_back(0);
        score.push_back(0);
        score.push_back(0);
    } else {
        while (file >> tmp_pseudo >> tmp_score) {
            if (!tmp_pseudo.empty())
                pseudo.push_back(tmp_pseudo);
            if (!tmp_score.empty())
                score.push_back(stoi(tmp_score));
        }
    }
    this->file.close();

    // On le vide
    this->file.open("scores", std::fstream::out | std::fstream::trunc);
    this->file.close();

    bool loop = true;
    int  id = 0;

    for (int i = 0; (i < score.size()) && loop; i++) {

        if (newscore > score[i]) {
            score[i] = newscore;
            loop = false;
            id = i;
        }
    }
    this->file.open("scores");

    IGUIEditBox    *input = guiEnv->addEditBox(L"", rect<s32>(MID_WIDTH - 250, MID_HEIGHT, MID_WIDTH + 250, MID_HEIGHT + 70));
    input->setMax(14);
    guiEnv->addStaticText(L"NEW HIGHSCORE !!", rect<s32>(MID_WIDTH - 180, MID_HEIGHT - 180, MID_WIDTH + 180, MID_HEIGHT - 130), true);

    guiEnv->addStaticText(L"ENTER YOUR NAME", rect<s32>(MID_WIDTH - 250, MID_HEIGHT - 80, MID_WIDTH + 250, MID_HEIGHT - 30), true);
    guiEnv->addButton(rect<s32>(MID_WIDTH - 250, MID_HEIGHT + 200, MID_WIDTH + 250, MID_HEIGHT + 290), 0, GUI_ID_CONFIRM_BUTTON, L"CONFIRM", L"Confirm your name");

    SAppContextNewSco *context = new SAppContextNewSco;
    if (context) {
       context->device = this->getDevice();
       context->counter = 0;
    } else
        throw std::string(strerror(ENOMEM));

    this->eventReceiver = new NewScoEventReceiver(*context, this->device, this->scenesStack, &this->stop, input, score, pseudo, id, &this->file);

    if (this->eventReceiver)
        device->setEventReceiver(this->eventReceiver);
    else
        throw std::string(strerror(ENOMEM));
}



/*
** 	Step 3: ANIMATE
** 	everything which need to move (= be recalculated) at each frame.
*/

void 	NewHighScore::animate(void) {
	
}



/*
** 	Step 4: RENDER
** 	Call every methods needed to display the scene (sceneManager and/or gui).
*/


void 	NewHighScore::render(void) {

	this->driver->beginScene(true, true, video::SColor(0,133,133,133));
	this->guiEnv->drawAll();
	this->driver->endScene();

    if (this->stop) {
        delete scenesStack->top();
        scenesStack->pop();
        delete scenesStack->top();
        scenesStack->pop();
        delete scenesStack->top();
        scenesStack->pop();
    }
}
