#pragma once



#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <image.hpp>



class sprite : public image {
private:
	const int x_lim;
	const int y_lim;

public:
	sprite(window& win, const char* path, SDL_Rect src, SDL_Rect des, const int x_lim, const int y_lim) :
	image(win, path, src, des), x_lim(x_lim - 1), y_lim(y_lim - 1) { }
	~sprite() { }

	int get_x_lim() const { return this->x_lim; }
	int get_y_lim() const { return this->y_lim; }
	int get_src_x_index() const { return this->src.x / src.w; }
	int get_src_y_index() const { return this->src.y / src.h; }

	void advance_x_frame();
	void advance_y_frame();
	void reset_src_x(const bool cond);
	void reset_src_y(const bool cond);

};