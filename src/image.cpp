#include <image.hpp>



void image::change_frame_pos(int x, int y) {
	this->src.x = x;
	this->src.y = y;
}

void image::change_frame_size(int w, int h) {
	this->src.w = w;
	this->src.h = h;
}

void image::change_pos(int x, int y) {
	this->des.x = x;
	this->des.y = y;
}

void image::change_size(int w, int h) {
	this->des.w = w;
	this->des.h = h;
}

void image::draw() const {
	SDL_RenderCopy(this->win.get_ren(), this->img, &(this->src), &(this->des));
}