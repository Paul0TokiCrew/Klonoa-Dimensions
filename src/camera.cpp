#include <camera.hpp>



void camera::update_cam(const vec2f new_ref) {
	const vec2f move = vec2f(new_ref - this->ref);
	this->cam_pos.x += move.x;
	this->cam_pos.y += move.y;
	this->ref = new_ref;
}