#include <game.hpp>


bool game::running = false;
std::queue<std::string> msgs;



float get_current_time() { return SDL_GetTicks() / 1000.0f; }

bool game::init() {
	static bool called = false;

	if (called) {
		msgs.push("WARNING: calling \"game::init()\" multiple times");
		return false;

	}

	called = true;
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
	    game::running = true;

	return initialized;
}