#include <sprite.hpp>



void sprite::advance(const int x_advance, const int y_advance) {
	if (this->index == this->reset_index) {
		this->change_frame_pos(0, 0);
		this->index = 0;
		return;

	}



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
	++(this->index);

}