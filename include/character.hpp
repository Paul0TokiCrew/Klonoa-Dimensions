#pragma once



#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include <vec2f.hpp>
#include <area.hpp>
#include <sprite.hpp>



#define IDLE 0
#define MOVE 1



class character {
private:
	vec2f xy, wh, vel, goal_vel, max_vel;
	sprite* r_sprites;
	sprite* l_sprites;
	sprite* current_sprite;
	short counter;

public:
	character(const vec2f xy, const vec2f wh, const vec2f vel, const vec2f max_vel, sprite* r_sprites, sprite* l_sprites) :
		xy(xy), wh(wh), vel(vel), goal_vel(vel), max_vel(max_vel), r_sprites(r_sprites), l_sprites(l_sprites), current_sprite(&(r_sprites[0])), counter(0) { }
	~character() { }

	vec2f get_xy() const { return this->xy; }
	vec2f get_wh() const { return this->wh; }
	vec2f get_vel() const { return this->vel; }
	vec2f get_goal_vel() const { return this->goal_vel; }
	vec2f get_max_vel() const { return this->max_vel; }
	sprite* get_r_sprites() const { return this->r_sprites; }
	sprite* get_l_sprites() const { return this->l_sprites; }
	sprite* get_current_sprite() const { return this->current_sprite; }
	short get_counter() const { return this->counter; }

	void update_sprites();
	void update_pos(const float delta_time, const area_manager area_man);
	void update_datas(const Uint8* key, const area_manager area_man);

};