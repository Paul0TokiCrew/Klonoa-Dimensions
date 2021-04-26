#include <map.hpp>



bool map::find_tile(const tile_id t) const {

	for (const auto i : this->tiles)
		if (i.id == t.id)
			return true;

	return false;
}

void map::register_tile_id(const tile_id t) {
	if (!(this->find_tile(t)))
		this->tiles.push_back(t);

}