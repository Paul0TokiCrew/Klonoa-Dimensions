#include <window.hpp>



void window::clear() const {
	SDL_RenderClear(this->ren);
}

void window::clear(const int r, const int g, const int b) const {
	SDL_SetRenderDrawColor(this->ren, r, g, b, 255);
	SDL_RenderClear(this->ren);
}

void window::clear(const int r, const int g, const int b, const int a) const {
	SDL_SetRenderDrawColor(this->ren, r, g, b, a);
	SDL_RenderClear(this->ren);
}

void window::render(const image& img) const {
	SDL_RenderCopy(this->ren, img.get_img(), &(img.get_src), &(img.get_des));
}

void window::render(const sprite& spr) const {
	SDL_RenderCopy(this->ren, spr.get_img(), &(spr.get_src), &(spr.get_des));
}

void window::update() const {
	SDL_RenderPresent(this->ren);
}