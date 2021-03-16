#include <game.hpp>



bool game::init() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		return false;
		
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
		return false;
		
	}

    this->running = true;
	return true;
}