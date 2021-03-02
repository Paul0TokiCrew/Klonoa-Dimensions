#include <character.hpp>



extern std::queue<std::string> msgs;

void character::update_pos(const float delta_time, const float fric, const area_manager area_man) {
	if (fric < 0)
		return;

	if (area_man.check_up_collision(this->xy, vec2f(this->xy.x + this->wh.x, this->xy.y + this->wh.y))) {
		msgs.push("up collision detected");

		if (this->vel.y < 0)
			this->vel.y = 0;

	}

	if (area_man.check_down_collision(this->xy, vec2f(this->xy.x + this->wh.x, this->xy.y + this->wh.y))) {
		msgs.push("down collision detected");

		if (this->vel.y > 0)
			this->vel.y = 0;

	}

	if (area_man.check_right_collision(this->xy, vec2f(this->xy.x + this->wh.x, this->xy.y + this->wh.y))) {
		msgs.push("right collision detected");

		if (this->vel.x > 0)
			this->vel.x = 0;

	}

	if (area_man.check_left_collision(this->xy, vec2f(this->xy.x + this->wh.x, this->xy.y + this->wh.y))) {
		msgs.push("left collision detected");

		if (this->vel.x < 0)
			this->vel.x = 0;

	}



	if (std::ceil(this->vel.x))
		this->xy.x += this->vel.x * delta_time;

	if (std::ceil(this->vel.y))
		this->xy.y += this->vel.y * delta_time;



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



	if (key[SDL_SCANCODE_Z] && !(this->counter)) {
		
		if (this->is_running) {
			this->max_vel = this->max_vel / vec2f(2, 2);
			this->is_running = false;

		} else {
			this->max_vel = this->max_vel * vec2f(2, 2);
			this->is_running = true;

		}

		this->counter = 10;

	}

	if (this->counter)
		--counter;

}