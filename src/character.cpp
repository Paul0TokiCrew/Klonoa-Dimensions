#include <character.hpp>



extern std::queue<std::string> msgs;

void character::switch_current_sprite(sprite& new_sprite) {
	current_sprite->change_frame_pos(0, 0);
	current_sprite = &(new_sprite);
}

void character::update_sprites() {
	if (this->current_sprite != nullptr)
		this->current_sprite->advance();



	if (this->goal_vel != vec2f(0)) {

		if (this->goal_vel.x > 0)
			this->switch_current_sprite(this->r_sprites[WALK]);

		else
			this->switch_current_sprite(this->l_sprites[WALK]);

	} else {
		if (this->current_sprite[0] == this->r_sprites[WALK])
			this->switch_current_sprite(this->r_sprites[IDLE]);

		else
			this->switch_current_sprite(this->l_sprites[IDLE]);

	}

}

void character::update_pos(const float delta_time, const area_manager area_man) {
	vec2f xy2 = vec2f(this->xy.x + this->wh.x, this->xy.y + this->wh.y), diff = vec2f(0, 0),
		move = vec2f(this->vel * vec2f(delta_time));

	float fric = area_man.get_fric(this->xy, xy2);

	if (area_man.check_up_collision(this->xy + move, xy2 + move, &diff)) {
		msgs.push("up collision detected");

		if (this->vel.y < 0) {
			this->vel.y = 0;
			move.y += diff.y;

		}

	}

	if (area_man.check_down_collision(this->xy + move, xy2 + move, &diff)) {
		msgs.push("down collision detected");

		if (this->vel.y > 0) {
			this->vel.y = 0;
			move.y += diff.y;

		}

	}

	if (area_man.check_right_collision(this->xy + move, xy2 + move, &diff)) {
		msgs.push("right collision detected");

		if (this->vel.x > 0) {
			this->vel.x = 0;
			move.x += diff.x;

		}

	}

	if (area_man.check_left_collision(this->xy + move, xy2 + move, &diff)) {
		msgs.push("left collision detected");

		if (this->vel.x < 0) {
			this->vel.x = 0;
			move.x += diff.x;

		}

	}



	if (std::ceil(this->vel.x))
		this->xy.x += move.x;

	if (std::ceil(this->vel.y))
		this->xy.y += move.y;



	if (std::ceil(this->vel.x) < std::ceil(this->goal_vel.x))
		this->vel.x += delta_time * fric;

	else if (std::ceil(this->vel.x) > std::ceil(this->goal_vel.x))
		this->vel.x -= delta_time * fric;



	if (std::ceil(this->vel.y) < std::ceil(this->goal_vel.y))
		this->vel.y += delta_time * fric;

	else if (std::ceil(this->vel.y) > std::ceil(this->goal_vel.y))
		this->vel.y -= delta_time * fric;

}

void character::update_datas(const Uint8* key, const area_manager area_man) {
	if (!area_man.check_down_collision(this->xy, vec2f(this->xy - this->wh)))
		this->goal_vel.y = this->max_vel.y;

	else
		this->goal_vel.y = 0;



	if (key[SDL_SCANCODE_RIGHT])
		this->goal_vel.x = this->max_vel.x;

	else if (key[SDL_SCANCODE_LEFT])
		this->goal_vel.x = -(this->max_vel.x);

	else
		this->goal_vel.x = 0;


	
	if (key[SDL_SCANCODE_Z])
		this->vel.y = -100;


	if (this->counter)
		--counter;

}