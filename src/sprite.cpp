#include <sprite.hpp>



void sprite::advance(const int x_advance, const int y_advance) {
	if (this->index == this->reset_index) {
		this->change_frame_pos(0, 0);
		this->index = 0;
		return;

	}



	int new_x = this->get_src().x, new_y = this->get_src().y;

	if (x_advance == 0)
		new_x += this->x_advance;

	else
		new_x += x_advance;

	if (y_advance == 0)
		new_y += this->y_advance;

	else
		new_y += y_advance;

	this->change_frame_pos(new_x, new_y);
	++(this->index);

}