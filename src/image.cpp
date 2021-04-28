#include <image.hpp>



void image::change_frame_pos(const int x, const int y) {
	this->src.x = x;
	this->src.y = y;
}

void image::change_frame_size(const int w, const int h) {
	this->src.w = w;
	this->src.h = h;
}

void image::change_pos(const int x, const int y) {
	this->des.x = x;
	this->des.y = y;
}

void image::change_size(const int w, const int h) {
	this->des.w = w;
	this->des.h = h;
}



void renderer::render(SDL_Renderer* ren) const {
	SDL_Rect src, des;

	for (const auto ent : this->ents) {

		const auto& tex = crd.get_comp<c_image>(ent);

		src = tex.img->get_src();
		des = tex.img->get_des();

		SDL_RenderCopy(ren, tex.img->get_img(), &src, &des);

	}

}