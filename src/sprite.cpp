#include <sprite.hpp>



void sprite::advance(const int x_advance, const int y_advance) {
	if (count < max_count) {
		++count;
		return;

	} else
		count = 0;

	if (this->index == this->reset_index) {
		this->change_frame_pos(0, 0);
		this->index = 0;
		return;

	}



	int new_x = this->get_src().x, new_y = this->get_src().y;

	if (x_advance == 0)
		new_x += this->x_move;

	else
		new_x += x_advance;

	if (y_advance == 0)
		new_y += this->y_move;

	else
		new_y += y_advance;

	this->change_frame_pos(new_x, new_y);
	++(this->index);

}