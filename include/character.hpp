#pragma once



#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include <vec2f.hpp>
#include <area.hpp>
#include <sprite.hpp>



class character {
private:
	vec2f xy, wh, vel, goal_vel, max_vel;
	sprite* current_sprite;
	short counter;

public:
	character(const vec2f xy, const vec2f wh, const vec2f vel, const vec2f max_vel, sprite* current_sprite) :
		xy(xy), wh(wh), vel(vel), goal_vel(vel), max_vel(max_vel), current_sprite(current_sprite), counter(0) { }
	~character() { }

	vec2f get_xy() const { return this->xy; }
	vec2f get_wh() const { return this->wh; }
	vec2f get_vel() const { return this->vel; }
	vec2f get_goal_vel() const { return this->goal_vel; }
	vec2f get_max_vel() const { return this->max_vel; }
	sprite* get_current_sprite() const { return this->current_sprite; }
	short get_counter() const { return this->counter; }

	void update_sprites();
	void update_pos(const float delta_time, const area_manager area_man);
	void update_datas(const Uint8* key, const area_manager area_man);

};