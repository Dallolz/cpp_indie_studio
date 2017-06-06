#ifndef __GAMEMANAGER_HPP__
# define __GAMEMANAGER_HPP__

# include <stack>
# include <vector>

# include "Bomberman.hpp"
# include "IScene.hpp"

class GameManager {

public:
	GameManager();
	~GameManager();

	bool 				initGame();
	void 				scenesHandler();
	void 				clear();

	bool 				loop;

private:
	void 				printFPS();

	IScene				*oldScene;
	std::stack<IScene *> scenesStack;
	IrrlichtDevice		*device;
};

#endif
