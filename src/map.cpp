#include <map.hpp>



bool map::find_tile(const tile_id t) const {

	for (const auto i : this->tiles)
		if (i.id == t.id)
			return true;

	return false;
}

bool map::find_tile(const char id) const {

	for (const auto i : this->tiles)
		if (i.id == id)
			return true;

	return false;
}

void map::register_tile_id(const tile_id t) {
	if (!(this->find_tile(t)))
		this->tiles.push_back(t);

}

void map::render(SDL_Renderer* ren) const {

	for (const auto i : lvl) {

		//if (this->find_tile(i))

	}

}