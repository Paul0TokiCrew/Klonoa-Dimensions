#include <iostream>
#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <window.hpp>
#include <image.hpp>
#include <area.hpp>
#include <character.hpp>
#include <camera.hpp>



//#define PRINTLN(txt) std::cout << txt << std::endl;
//#define GRAVITY 10000
//#define FRIC 400



//std::queue<std::string> msgs;



class game {
private:
	bool running;
	static float get_current_time() { return SDL_GetTicks() / 1000.0f; }

public:
	bool init();

};