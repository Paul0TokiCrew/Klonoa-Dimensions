#pragma once



#include <string>
#include <SDL2/SDL.h>
#include <log.hpp>
#include <ECS.hpp>
#include <area.hpp>



struct c_player_keys { std::string keys[3]; };

class player : public system {
public:
	player() { }
	~player() { }

	void update(const Uint8* key, const area_manager& area_man) const;
	
};