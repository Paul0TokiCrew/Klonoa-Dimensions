#include <camera.hpp>



void camera::update_cam(const vec2f new_ref) {
	vec2f move = this->cam_pos + vec2f(new_ref - this->ref);
	if (move.x < this->lim.x)
		move.x -= move.x - this->lim.x;

	if (move.y < this->lim.y)
		move.y -= move.y - this->lim.y;

	this->cam_pos = move;
	this->ref = new_ref;
}