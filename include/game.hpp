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



class game {
private:
	static bool running;

public:
	static bool init();
	static bool is_running();

};