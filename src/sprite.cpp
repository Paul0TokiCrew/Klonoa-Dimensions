#include <sprite.hpp>



void sprite::advance(const int x_advance = 0, const int y_advance = 0) {
	int x_move, y_move;

	if (x_advance == 0)
		x_move = this->x_advance;

	else
		x_move = x_advance;

	if (x_advance == 0)
		x_move = this->x_advance;

	else
		x_move = x_advance;



	this->change_frame_pos(x_move, y_move);

}