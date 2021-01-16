#include <character.hpp>



int character::x = 150, character::y = 150,
	character::w = 64, character::h = 64;

player_data character::dir = player_data(RIGHT, LEFT),
	character::action1 = player_data(STAND, JUMP),
	character::action2 = player_data(IDLE, MOVE);



void move_up() {

	for (int i = 0; i < 15; ++i)
		if (object::check_up_collision(CHARACTER_REC))
			break;

		else
			--character::y;

}

void move_down() {

	for (int i = 0; i < 15; ++i)
		if (object::check_down_collision(CHARACTER_REC))
			break;

		else
			++character::y;

}

void move_right(character* obj) {

	for (int i = 0; i < obj->speed * 2; ++i)
		if (object::check_right_collision(CHARACTER_REC))
			break;

		else
			++character::x;

}

void move_left(character* obj) {

	for (int i = 0; i < obj->speed * 2; ++i)
		if (object::check_left_collision(CHARACTER_REC))
			break;

		else
			--character::x;

}