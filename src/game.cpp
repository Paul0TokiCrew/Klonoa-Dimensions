#include <game.hpp>



std::queue<std::string> msgs;



float get_current_time() { return SDL_GetTicks() / 1000.0f; }

bool game::init() {
	bool initialized = true;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		msgs.push("ERROR: could not initialize SDL library");
		initialized = false;
		
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
		msgs.push("ERROR: could not initialize SDL_image library");
		initialized = false;
		
	}

	if (initialized)
	    this->running = true;

	return initialized;
}