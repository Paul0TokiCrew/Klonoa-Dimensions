#pragma once



#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <window.hpp>



class image {
protected:
	SDL_Texture* img;
	SDL_Rect src, des;
	window& win;

public:
	image(window& win, const char* path, const SDL_Rect src, const SDL_Rect des) :
	img(nullptr), src(src), des(des), win(win) {
		this->img = IMG_LoadTexture(this->win.get_ren(), path);
	}
	~image() {
		SDL_DestroyTexture(this->img);
	}

	int get_src_x() const { return this->src.x; }
	int get_src_y() const { return this->src.y; }
	int get_src_w() const { return this->src.w; }
	int get_src_h() const { return this->src.h; }

	int get_des_x() const { return this->des.x; }
	int get_des_y() const { return this->des.y; }
	int get_des_w() const { return this->des.w; }
	int get_des_h() const { return this->des.h; }

	void change_frame_pos(const int x, const int y);
	void change_frame_size(const int w, const int h);
	void change_pos(const int x, const int y);
	void change_size(const int w, const int h);

	void draw() const;

};