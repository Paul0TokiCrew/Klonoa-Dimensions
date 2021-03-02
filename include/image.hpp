#pragma once



#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <window.hpp>



class image {
protected:
	SDL_Texture* img;
	SDL_Rect src, des;
	const SDL_Rect old_des;
	const window& win;

public:
	image(const window& win, const char* path, const SDL_Rect src, const SDL_Rect des) :
		img(nullptr), src(src), des(des), old_des(des), win(win) {
		this->img = IMG_LoadTexture(this->win.get_ren(), path);
	}
	~image() {
		SDL_DestroyTexture(this->img);
	}

	SDL_Rect get_src() const { return this->src; }
	SDL_Rect get_des() const { return this->des; }
	SDL_Rect get_old_des() const { return this->old_des; }

	void change_frame_pos(const int x, const int y);
	void change_frame_size(const int w, const int h);
	void change_pos(const int x, const int y);
	void change_size(const int w, const int h);

	void draw() const;

};