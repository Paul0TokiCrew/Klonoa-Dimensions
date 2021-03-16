#include <game.hpp>



bool game::init() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    this->running = true;
}