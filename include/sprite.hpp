#pragma once



#include <SDL2/SDL.h>
#include <image.hpp>



class sprite : public image {
private:
	int index, reset_index,
		x_move, y_move,
		count, max_count;

public:
	sprite(SDL_Renderer* ren, const char* path, const SDL_Rect src, const SDL_Rect des, const int index = 0, const int reset_index = 0, const int x_move = 0, const int y_move = 0, const int max_count = 0) :
		image(ren, path, src, des), index(index), reset_index(reset_index), x_move(x_move), y_move(y_move), count(0), max_count(max_count) { }

	~sprite() { }

	void set_x_move(const int x_move) { this->x_move = x_move; }
	void set_y_move(const int y_move) { this->y_move = y_move; }

	int get_index() const { return this->index; }
	int get_reset_index() const { return this->reset_index; }
	int get_x_move() const { return this->x_move; }
	int get_y_move() const { return this->y_move; }

	void advance(const int x_advance = 0, const int y_advance = 0);

};