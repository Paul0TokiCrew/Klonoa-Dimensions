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
	int w, h, tw, th;

public:
	map(const std::string lvl = "", const int w = 0, const int h = 0, const int tw = 64, const int th = 64) :
		lvl(lvl), tiles { }, w(w), h(h), tw(tw), th(th) { }
	~map() { }

	void set_lvl(const std::string lvl) { this->lvl = lvl; }

	std::string get_lvl() const { return this->lvl; }
	int get_w() const { return this->w; }
	int get_h() const { return this->h; }

	void register_tile_id(const tile_id t);
	image* find_tile(const tile_id t) const;
	image* find_tile(const char id) const;

	void render(SDL_Renderer* ren) const;

};