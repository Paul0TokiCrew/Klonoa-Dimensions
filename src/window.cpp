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
	SDL_Rect src = img.get_src(),
		des = img.get_des();
	SDL_RenderCopy(this->ren, img.get_img(), &src, &des);
}

void window::render(const sprite& spr) const {
	SDL_Rect src = spr.get_src(),
		des = spr.get_des();
	SDL_RenderCopy(this->ren, spr.get_img(), &src, &des);
}

void window::render(const area_manager& area_man) const {

	for (unsigned i = 0; i < area_man.get_img_areas_size(); ++i) {

		image& img = area_man.get_img_area(i).first[0];
		SDL_Rect src = img.get_src(),
		des = img.get_des();

		SDL_RenderCopy(this->ren, img.get_img(), &src, &des);

	}

}

void window::render(const character& chr) const {
	sprite& spr = chr.get_current_sprite()[0];
	SDL_Rect src = spr.get_src(),
		des = spr.get_des();
	SDL_RenderCopy(this->ren, spr.get_img(), &src, &des);;
}

void window::update() const {
	SDL_RenderPresent(this->ren);
}