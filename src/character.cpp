#include <character.hpp>



void character::switch_current_sprite(sprite& new_sprite) {
	if (&new_sprite == this->current_sprite)
		return;

	current_sprite->change_frame_pos(0, 0);
	current_sprite = &(new_sprite);
}

void character::update_sprites(const c_movement& movement) {
	if (this->current_sprite != nullptr)
		this->current_sprite->advance();



	if (movement.goal_vel != vec2f(0)) {

		if (movement.dir.x > 0)
			this->switch_current_sprite(this->r_sprites[WALK]);

		else
			this->switch_current_sprite(this->l_sprites[WALK]);

	} else {
		if (movement.dir.x > 0)
			this->switch_current_sprite(this->r_sprites[IDLE]);

		else
			this->switch_current_sprite(this->l_sprites[IDLE]);

	}

}