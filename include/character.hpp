#pragma once



#include <SDL2/SDL.h>
#include <vec2f.hpp>
#include <log.hpp>
#include <area.hpp>
#include <sprite.hpp>



#define IDLE 0
#define WALK 1
#define JUMP 2
#define FALL 3



class character {
protected:
	vec2f xy, wh, dir, vel, goal_vel, max_vel;
	sprite* r_sprites;
	sprite* l_sprites;
	sprite* current_sprite;
	const area_manager* current_area;
	short counter;

	void switch_current_sprite(sprite& new_sprite);

public:
	character(const vec2f xy, const vec2f wh, const vec2f dir,
		const vec2f vel, const vec2f max_vel,
		sprite* r_sprites, sprite* l_sprites,
		const area_manager* current_area = nullptr) :
		xy(xy), wh(wh), dir(dir), vel(vel), goal_vel(vel), max_vel(max_vel),
		r_sprites(r_sprites), l_sprites(l_sprites), current_sprite(&(r_sprites[IDLE])),
		current_area(current_area),
		counter(0) { }
	~character() { }

	vec2f get_xy() const { return this->xy; }
	vec2f get_wh() const { return this->wh; }
	vec2f get_dir() const { return this->dir; }
	vec2f get_vel() const { return this->vel; }
	vec2f get_goal_vel() const { return this->goal_vel; }
	vec2f get_max_vel() const { return this->max_vel; }
	sprite* get_r_sprites() const { return this->r_sprites; }
	sprite* get_l_sprites() const { return this->l_sprites; }
	sprite* get_current_sprite() const { return this->current_sprite; }
	const area_manager* get_current_area() const { return this->current_area; }
	short get_counter() const { return this->counter; }

	void update_sprites();
	void update_pos(const float delta_time, const area_manager area_man);
	void update_datas(const Uint8* key, const area_manager area_man);

};