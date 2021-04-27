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

	for (const auto i : lvl) {

		image* tile = this->find_tile(i);
		if (!tile)
			continue;

		SDL_RenderCopy(ren, tile->get_img(), &src, &des);

	}

}