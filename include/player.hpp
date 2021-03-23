#pragma once



#include <log.hpp>
#include <camera.hpp>
#include <character.hpp>



class player : public character {
private:
	const char* name;
	camera cam;

public:
	player(const char* name,
		const vec2f xy, const vec2f wh, const vec2f dir,
		const vec2f vel, const vec2f max_vel,
		sprite* r_sprites, sprite* l_sprites,
		const area_manager* current_area = nullptr) :
		character(xy, wh, dir, vel, max_vel, r_sprites, l_sprites, current_area),
		name(name), cam(camera(xy)) { }
	~player() { }

};