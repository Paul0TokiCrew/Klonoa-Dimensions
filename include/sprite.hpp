#pragma once



#include <SDL2/SDL.h>
#include <image.hpp>



class sprite : public image {
private:
    int index,
        x_advance, y_advance;

public:
    sprite(const window& win, const char* path, const SDL_Rect src, const SDL_Rect des, int index = 0, int x_advance = 0, int y_advance = 0) :
		image(win, path, src, des), index(index), x_advance(x_advance), y_advance(y_advance) { }

	int get_index() const { return this->index; }
	int get_x_advance() const { return this->x_advance; }
	int get_y_advance() const { return this->y_advance; }

};