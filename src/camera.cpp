#include <camera.hpp>



void camera::update_cam(const vec2f new_ref) {
	this->cam_pos.x += new_ref.x - this->ref.x;
	this->cam_pos.y += new_ref.y - this->ref.y;
	this->ref = new_ref;
}