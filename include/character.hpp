#pragma once



#include <SDL2/SDL.h>
#include <physics.hpp>
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
	sprite* r_sprites;
	sprite* l_sprites;
	sprite* current_sprite;

	void switch_current_sprite(sprite& new_sprite);

public:
	character(sprite* r_sprites, sprite* l_sprites) :
		r_sprites(r_sprites), l_sprites(l_sprites), current_sprite(&(r_sprites[IDLE])),
	~character() { }

	sprite* get_r_sprites() const { return this->r_sprites; }
	sprite* get_l_sprites() const { return this->l_sprites; }
	sprite* get_current_sprite() const { return this->current_sprite; }

	void update_sprites(const c_movement& movement);

};