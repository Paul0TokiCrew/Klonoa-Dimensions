#include <player.hpp>



void player::update(const Uint8* key, const area_manager& area_man) {

	for (const auto& ent : this->ents) {

		auto& player_keys = crd.get_comp<c_player_keys>(ent);
		auto& position = crd.get_comp<c_position>(ent);
		auto& movement = crd.get_comp<c_movement>(ent);



		const unsigned int up = player_keys.keys[UP],
			right = player_keys.keys[RIGHT],
			left = player_keys.keys[LEFT];

		const vec2f xy2 = vec2f(position.xy - position.wh);

		if (!area_man.check_down_collision( { position.xy, xy2 } )) {
			movement.goal_vel.y = movement.max_vel.y;

			if (std::ceil(movement.vel.y) >= 0)
				movement.dir.y = 1;

		} else
			movement.goal_vel.y = 0;




		if (key[right]) {
			movement.goal_vel.x = movement.max_vel.x;
			movement.dir.x = 1;

		} else if (key[left]) {
			movement.goal_vel.x = -(movement.max_vel.x);
			movement.dir.x = -1;

		} else
			movement.goal_vel.x = 0;


		
		if (key[up]) {
			movement.vel.y = -100;
			movement.dir.y = -1;

		}


		if (this->counter)
			--counter;

	}

}
