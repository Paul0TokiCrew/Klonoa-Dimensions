#include <physics.hpp>



void physics::update(const float delta_time, const area_manager& area_man) const {

	for (const auto& ent : this->ents) {

		c_position& position = crd.get_comp<c_position>(ent);
		c_movement& movement = crd.get_comp<c_movement>(ent);



		vec2f xy2 = vec2f(position.xy + position.wh),
			move = vec2f(movement.vel * vec2f(delta_time)),
			diff = vec2f(0, 0);

		const float fric = area_man.get_fric(position.xy, xy2);



		if (area_man.check_up_collision(position.xy + move, xy2 + move, &diff)) {
			msgs.push("up collision detected");

			if (movement.vel.y < 0) {
				movement.vel.y = 0;
				move.y += diff.y;

			}

		}

		if (area_man.check_down_collision(position.xy + move, xy2 + move, &diff)) {
			msgs.push("down collision detected");

			if (movement.vel.y > 0) {
				movement.vel.y = 0;
				move.y += diff.y;

			}

		}

		if (area_man.check_right_collision(position.xy + move, xy2 + move, &diff)) {
			msgs.push("right collision detected");

			if (movement.vel.x > 0) {
				movement.vel.x = 0;
				move.x += diff.x;

			}

		}

		if (area_man.check_left_collision(position.xy + move, xy2 + move, &diff)) {
			msgs.push("left collision detected");

			if (movement.vel.x < 0) {
				movement.vel.x = 0;
				move.x += diff.x;

			}

		}



		if (std::ceil(movement.vel.x))
			position.xy.x += move.x;

		if (std::ceil(movement.vel.y))
			position.xy.y += move.y;



		if (std::ceil(movement.vel.x) < std::ceil(movement.goal_vel.x))
			movement.vel.x += delta_time * fric;

		else if (std::ceil(movement.vel.x) > std::ceil(movement.goal_vel.x))
			movement.vel.x -= delta_time * fric;



		if (std::ceil(movement.vel.y) < std::ceil(movement.goal_vel.y))
			movement.vel.y += delta_time * fric;

		else if (std::ceil(movement.vel.y) > std::ceil(movement.goal_vel.y))
			movement.vel.y -= delta_time * fric;


	}

}