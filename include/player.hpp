#pragma once



#include <string>
#include <SDL2/SDL.h>
#include <log.hpp>
#include <ECS.hpp>
#include <physics.hpp>
#include <vec2f.hpp>
#include <area.hpp>



#define UP 0
#define RIGHT 1
#define LEFT 2



struct c_player_keys { unsigned int keys[3]; };

class player : public system {
private:
	short counter;

public:
	player() :
		counter(0) { }
	~player() { }

	void update(const Uint8* key, const area_manager& area_man);
	
};