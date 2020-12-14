#include "window.hpp"

void window::clear() const {
	SDL_RenderClear(this->ren);
}

void window::clear(int r, int g, int b, int a = 255) const {
	SDL_SetRenderDrawColor(this->ren, r, g, b, a);
	SDL_RenderClear(this->ren);
}

void window::update() const {
	SDL_RenderPresent(this->ren);
}
