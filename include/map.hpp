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

public:
	map(const std::string lvl = "") :
		lvl(lvl) { }
	~map() { }

	std::string get_lvl() const { return this->lvl; }
	void set_lvl(const std::string lvl) { this->lvl = lvl; }

};