#include "GameManager.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(lib, "irrKlang.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main() {
	
	try {
		GameManager gm;

		if (!gm.initGame())
			return (EXIT_FAILURE);

    	while (gm.loop) {
			gm.scenesHandler();
		}
		gm.clear();

	} catch (std::string err_msg) {
		std::cerr << err_msg << std::endl;
	}
	return (0);
}	
