#include "GameManager.hpp"
#include "MainMenu.hpp"

GameManager::GameManager() { 
	this->loop = true;
	this->oldScene = NULL;
}

GameManager::~GameManager() { }

bool 	GameManager::initGame() {

	if (!(device = createDevice(video::EDT_OPENGL, dimension2d<u32>(WIN_WIDTH, WIN_HEIGHT), 16,
	 false, false, true, 0))) {
		throw std::string(ERR_GM_DEVICE);
		return (false);
	}
	device->setResizable(false);

	if (!(soundEngine = createIrrKlangDevice())) {
		throw std::string(ERR_GM_ENGINE);
		return (false);
	}

    this->device->setWindowCaption(getStringw(GAME_NAME).c_str());

    // on init la stack avec le menu principal
    MainMenu *mainMenu = new MainMenu(this->device, this->soundEngine, &scenesStack);
    scenesStack.push(mainMenu);

    return (true);
}

void 	GameManager::clear() { 
	this->device->drop();
	this->soundEngine->drop();

	int size = scenesStack.size();

	while (!scenesStack.empty()) {
		delete scenesStack.top();
		scenesStack.pop();
	}
}

void 	GameManager::printFPS() {

	static int 	lastFPS;

	int fps = scenesStack.top()->getDriver()->getFPS();

	if (fps != lastFPS) {
		std::string windowName = GAME_NAME;
		windowName += " - FPS: ";
		windowName += to_string(fps);
		this->device->setWindowCaption(getStringw(windowName).c_str());
		lastFPS = fps;
	}
}

void 	GameManager::scenesHandler() {

	int mapID = 0;

	while (device->run() && scenesStack.top()->getDriver()) {

		if (scenesStack.size() < 1)
			throw std::string(ERR_GM_EMPTYSTACK);
		else {
			if (oldScene != scenesStack.top()) {
				
				scenesStack.top()->init(&mapID);
				oldScene = scenesStack.top();

			}
			scenesStack.top()->animate();
			scenesStack.top()->render();
		}

		this->printFPS();
	}
	this->loop = false;
}
