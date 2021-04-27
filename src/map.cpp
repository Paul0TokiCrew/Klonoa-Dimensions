#include <map.hpp>



image* map::find_tile(const tile_id t) const {

	for (const auto i : this->tiles)
		if (i.id == t.id)
			return i.tile;

	return nullptr;
}

image* map::find_tile(const char id) const {

	for (const auto i : this->tiles)
		if (i.id == id)
			return i.tile;

	return nullptr;
}

void map::register_tile_id(const tile_id t) {
	if (!(this->find_tile(t)))
		this->tiles.push_back(t);

}

void map::render(SDL_Renderer* ren) const {
	SDL_Rect src, des;

	for (int y = 0; y < this->h; ++y) {

		for (int x = 0; x < this->w; ++x) {
		
				image* tile = this->find_tile(this->lvl[y * w + x]);
				if (!tile)
					continue;

				src = tile->get_src();
				des.w = this->tw;
				des.h = this->th;
				des.x = x * des.w;
				des.y = y * des.h;
		
				SDL_RenderCopy(ren, tile->get_img(), &src, &des);
		
		}
	
	}

}