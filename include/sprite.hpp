#pragma once



#include <SDL2/SDL.h>
#include <image.hpp>



class sprite : public image {
private:
    int index,
        x_advance, y_advance;

public:
    sprite(const window& win, const char* path, const SDL_Rect src, const SDL_Rect des, const int index = 0, const int x_advance = 0, const int y_advance = 0) :
		image(win, path, src, des), index(index), x_advance(x_advance), y_advance(y_advance) { }

	void set_x_advance(const int x_advance) { this->x_advance = x_advance; }
	void set_y_advance(const int y_advance) { this->y_advance = y_advance; }

	int get_index() const { return this->index; }
	int get_x_advance() const { return this->x_advance; }
	int get_y_advance() const { return this->y_advance; }

};