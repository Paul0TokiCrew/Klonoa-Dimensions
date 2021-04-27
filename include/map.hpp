#pragma once



#include <string>
#include <vector>
#include <image.hpp>



struct tile_id {
	const char id;
	image* tile;

};

class map {
private:
	std::string lvl;
	std::vector<tile_id> tiles;

public:
	map(const std::string lvl = "") :
		lvl(lvl), tiles { } { }
	~map() { }

	std::string get_lvl() const { return this->lvl; }
	void set_lvl(const std::string lvl) { this->lvl = lvl; }

	bool find_tile(const tile_id t) const;
	void register_tile_id(const tile_id t);

	void render(SDL_Renderer* ren) const;

};