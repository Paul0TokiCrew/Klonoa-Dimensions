#include <sprite.hpp>



void sprite::advance_x_frame() {
	this->src.x += this->src.w;
	if (this->get_src_x_index() > this->x_lim)
		this->src.x = 0;

}

void sprite::advance_y_frame() {
	this->src.y += this->src.h;
	if (this->get_src_y_index() > this->y_lim)
		this->src.y = 0;

}

void sprite::reset_src_x(const bool cond) {
	if (cond)
		this->src.x = 0;

}

void sprite::reset_src_y(const bool cond) {
	if (cond)
		this->src.y = 0;

}