#ifndef 	__BOMBERMAN_HPP__
# define 	__BOMBERMAN_HPP__

# include	"irrlicht.h"
# include	<iostream>


/* ERROR HANDLING */

# include 	<errno.h>
# include 	<string.h>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
//using namespace irrklang;
using namespace std;

/* UTILS FUNCTIONS PROTOTYPES */

irr::core::stringw getStringw(std::string);
void mySetSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin);


/* VARIABLES */

# define GAME_NAME	"BomberMan3D"
# define MAX_FPS 	144
# define WIN_HEIGHT 720
# define MID_HEIGHT (WIN_HEIGHT / 2)

# define WIN_WIDTH 	1280
# define MID_WIDTH 	(WIN_WIDTH / 2)


/* CUSTOM ERROR MESSAGES */

# define ERR_GM_DEVICE 		"(GameManager) Failed to create a device."
# define ERR_GM_ENGINE		"(GameManager) Failed to create a sound engine."
# define ERR_GM_EMPTYSTACK 	"(GameManager) Failed to find a scene to display."
# define ERR_SCO_CANTLOAD	"(ScoreMenu) Failed to load score file."

#endif
