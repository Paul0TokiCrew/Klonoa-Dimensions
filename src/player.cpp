#include <player.hpp>



void player::update(const Uint8* key, const area_manager& area_man) const {

	for (auto i : this->ents) {

		/*if (!area_man.check_down_collision(this->xy, vec2f(this->xy - this->wh))) {
			this->goal_vel.y = this->max_vel.y;

			if (std::ceil(this->vel.y) >= 0)
				this->dir.y = 1;

		} else
			this->goal_vel.y = 0;




		if (key[SDL_SCANCODE_RIGHT]) {
			this->goal_vel.x = this->max_vel.x;
			this->dir.x = 1;

		} else if (key[SDL_SCANCODE_LEFT]) {
			this->goal_vel.x = -(this->max_vel.x);
			this->dir.x = -1;

		} else
			this->goal_vel.x = 0;


		
		if (key[SDL_SCANCODE_SPACE]) {
			this->vel.y = -100;
			this->dir.y = -1;

		}


		if (this->counter)
			--counter;*/

	}

}