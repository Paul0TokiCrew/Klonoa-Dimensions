#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <window.hpp>
#include <image.hpp>
#include <sprite.hpp>
#include <character.hpp>
#include <object.hpp>



#define W 720
#define H 480

#define FPS 18

#define ADD_BORDERS object::add_obj( { 0, 0, W, 0 }, "u" );	\
	object::add_obj( { 0, 0, 0, H }, "l" );					\
	object::add_obj( { W, 0, 0, H }, "r" );					\
	object::add_obj( { 0, H, W, 0 }, "d" );



extern void move_up();
extern void move_down();
extern void move_left(character* obj);
extern void move_right(character* obj);



int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);



	bool game_over = false,
		attack = false;
	int jump_count = -1,
		swicth_count = 0;
	const int delay = 1000 / FPS;



	enum { NORMAL, SAMURAI } klonoa_mode = NORMAL;



	window win = window("Klonoa Dimensions - Cheesai Crystal", W, H);
	image harold = image(win, "res/textures/hide the pain.jpg", { 0, 0, 1200, 800 }, { 0, 0, W, H } ),
		putin = image(win, "res/textures/putin.jpg", { 0, 0, 1200, 1200 }, {0, 0, 1200, 1200} ),
		* background = &harold;

	sprite kil = sprite(win, "res/sprites/klonoa/character/Klonoa Idle Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 22, 1),
		kir = sprite(win, "res/sprites/klonoa/character/Klonoa Idle Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 22, 1),
		kwl = sprite(win, "res/sprites/klonoa/character/Klonoa Walk Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 4, 1),
		kwr = sprite(win, "res/sprites/klonoa/character/Klonoa Walk Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 4, 1),
		kjl = sprite(win, "res/sprites/klonoa/character/Klonoa Jump Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 6, 1),
		kjr = sprite(win, "res/sprites/klonoa/character/Klonoa Jump Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 6, 1),
		kfl = sprite(win, "res/sprites/klonoa/character/Klonoa Fall Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 5, 1),
		kfr = sprite(win, "res/sprites/klonoa/character/Klonoa Fall Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 5, 1),
		kwbl = sprite(win, "res/sprites/klonoa/character/Klonoa Wind Bullet Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 11, 1),
		kwbr = sprite(win, "res/sprites/klonoa/character/Klonoa Wind Bullet Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 11, 1),
		kwcl = sprite(win, "res/sprites/klonoa/character/Klonoa Wind Cut Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 5, 1),
		kwcr = sprite(win, "res/sprites/klonoa/character/Klonoa Wind Cut Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 5, 1),

		vil = sprite(win, "res/sprites/vanda/character/Vanda Idle Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 22, 1),
		vir = sprite(win, "res/sprites/vanda/character/Vanda Idle Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 22, 1),
		vwl = sprite(win, "res/sprites/vanda/character/Vanda Walk Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 4, 1),
		vwr = sprite(win, "res/sprites/vanda/character/Vanda Walk Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 4, 1),
		vjl = sprite(win, "res/sprites/vanda/character/Vanda Jump Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 6, 1),
		vjr = sprite(win, "res/sprites/vanda/character/Vanda Jump Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 6, 1),
		vfl = sprite(win, "res/sprites/vanda/character/Vanda Fall Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 5, 1),
		vfr = sprite(win, "res/sprites/vanda/character/Vanda Fall Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 5, 1),
		vkl = sprite(win, "res/sprites/vanda/character/Vanda Kick Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 8, 1),
		vkr = sprite(win, "res/sprites/vanda/character/Vanda Kick Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 8, 1),
		* current_sprite = &kil,

		wbl = sprite(win, "res/sprites/klonoa/attacks/Wind Bullet Left.png", { 0, 0, 32, 16 }, { character::x - character::w, character::y, character::w * 2, character::h }, 11, 1),
		wbr = sprite(win, "res/sprites/klonoa/attacks/Wind Bullet Right.png", { 0, 0, 32, 16 }, { character::x, character::y, character::w * 2, character::h }, 11, 1),
		wcl = sprite(win, "res/sprites/klonoa/attacks/Wind Cut Left.png", { 0, 0, 32, 16 }, { character::x - character::w, character::y, character::w * 2, character::h }, 5, 1),
		wcr = sprite(win, "res/sprites/klonoa/attacks/Wind Cut Right.png", { 0, 0, 32, 16 }, { character::x, character::y, character::w * 2, character::h }, 5, 1),
		kl = sprite(win, "res/sprites/vanda/attacks/Kick Left.png", { 0, 0, 32, 16 }, { character::x - character::w, character::y, character::w * 2, character::h }, 8, 1),
		kr = sprite(win, "res/sprites/vanda/attacks/Kick Right.png", { 0, 0, 32, 16 }, { character::x, character::y, character::w * 2, character::h }, 8, 1),
		* current_attack = &wbl,

		wsl = sprite(win, "res/sprites/klonoa/wind sword/Wind Sword Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 1, 1),
		wsr = sprite(win, "res/sprites/klonoa/wind sword/Wind Sword Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 1, 1),
		wsjl = sprite(win, "res/sprites/klonoa/wind sword/Wind Sword Jump Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 6, 1),
		wsjr = sprite(win, "res/sprites/klonoa/wind sword/Wind Sword Jump Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 6, 1),
		wsfl = sprite(win, "res/sprites/klonoa/wind sword/Wind Sword Fall Left.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 5, 1),
		wsfr = sprite(win, "res/sprites/klonoa/wind sword/Wind Sword Fall Right.png", { 0, 0, 16, 16 }, { character::x, character::y, character::w, character::h }, 5, 1),
		* current_ws_sprite = nullptr;

	character klonoa = character(5, 12, true),
		vanda = character(7, 5, false),
		* current_character = &klonoa;



	ADD_BORDERS
	//object::add_obj( { 200, H / 2 + 100, 300, 64 }, putin, "collision");
	//object::add_obj( { 0, H - 50, 125, 50 }, putin, "collision");
	//object::add_obj( { 500, H / 2 + 40, W - 400, 90 }, putin, "collision");



	auto update_actions = [&] () -> void {
		const Uint8* key_state = SDL_GetKeyboardState(nullptr);

		if (key_state[SDL_SCANCODE_Z] && jump_count < current_character->get_jump_height() && (character::action1 != FALL || current_character->get_jump_many_times()) ) {
			character::action1 = JUMP;
			++jump_count;

		} else if (!object::check_down_collision(CHARACTER_REC)) {
			character::action1 = FALL;
			if (jump_count > -1)
				--jump_count;

		} else {
			character::action1 = STAND;
			jump_count = -1;

		}



		if (key_state[SDL_SCANCODE_LEFT]) {
			character::action2 = MOVE;
			character::dir = LEFT;

		} else if (key_state[SDL_SCANCODE_RIGHT]) {
			character::action2 = MOVE;
			character::dir = RIGHT;

		} else
			character::action2 = IDLE;



		if (key_state[SDL_SCANCODE_X] || attack)
			attack = true;

		else
			attack = false;



		if (key_state[SDL_SCANCODE_C] && !attack && swicth_count == 0) {
			if (current_character == &klonoa)
				current_character = &vanda;

			else
				current_character = &klonoa;

			swicth_count = 10;

		} else if (swicth_count > 0)
			--swicth_count;



		if (key_state[SDL_SCANCODE_S] && !attack && swicth_count == 0) {
			if (klonoa_mode == NORMAL)
				klonoa_mode = SAMURAI;

			else
				klonoa_mode = NORMAL;

			swicth_count = 10;

		} else if (swicth_count > 0)
			--swicth_count;

	};



	auto def_sprite_by_dir = [&] (sprite& left, sprite& right) -> sprite* {
		if (character::dir == LEFT)
			return &left;

		return &right;
	};

	auto def_sprite_by_character = [&] (sprite& k, sprite& v) -> sprite& {
		if (current_character == &klonoa)
			return k;

		return v;
	};

	auto update_sprites = [&] () -> void {
		if (character::action1 == STAND || current_sprite->get_src_x_index() < current_sprite->get_x_lim()) {
			current_sprite->advance_x_frame();

			if (klonoa_mode == SAMURAI && current_ws_sprite != nullptr)
				current_ws_sprite->advance_x_frame();

		}



		if (attack && current_attack->get_src_x_index() >= current_attack->get_x_lim()) {
			attack = false;
			current_attack->change_frame_pos(0, 0);

		} else if (attack)
			current_attack->advance_x_frame();



		if (character::action1 == FALL) {
			current_sprite = def_sprite_by_dir(def_sprite_by_character(kfl, vfl), def_sprite_by_character(kfr, vfr));

			if (current_character == &klonoa && klonoa_mode == SAMURAI)
				current_ws_sprite = def_sprite_by_dir(wsfl, wsfr);

		} else if (character::action1 == JUMP) {
			current_sprite = def_sprite_by_dir(def_sprite_by_character(kjl, vjl), def_sprite_by_character(kjr, vjr));

			if (current_character == &klonoa && klonoa_mode == SAMURAI)
				current_ws_sprite = def_sprite_by_dir(wsjl, wsjr);

		} else if (character::action1 == STAND && character::action2 == MOVE) {
			current_sprite = def_sprite_by_dir(def_sprite_by_character(kwl, vwl), def_sprite_by_character(kwr, vwr));

			if (current_character == &klonoa && klonoa_mode == SAMURAI)
				current_ws_sprite = def_sprite_by_dir(wsl, wsr);

		} else if (attack && character::action1 == STAND && character::action2 == IDLE) {

			if (klonoa_mode == NORMAL)
				current_sprite = def_sprite_by_dir(def_sprite_by_character(kwbl, vkl), def_sprite_by_character(kwbr, vkr));

			else
				current_sprite = def_sprite_by_dir(def_sprite_by_character(kwcl, vkl), def_sprite_by_character(kwcr, vkr));

			current_ws_sprite = nullptr;

		} else {
			current_sprite = def_sprite_by_dir(def_sprite_by_character(kil, vil), def_sprite_by_character(kir, vir));
			if (current_character == &klonoa && klonoa_mode == SAMURAI)
				current_ws_sprite = def_sprite_by_dir(wsl, wsr);

		}



		if (attack) {
			if (klonoa_mode == NORMAL)
				current_attack = def_sprite_by_dir(def_sprite_by_character(wbl, kl), def_sprite_by_character(wbr, kr));

			else
				current_attack = def_sprite_by_dir(def_sprite_by_character(wcl, kl), def_sprite_by_character(wcr, kr));

		}



		kil.reset_src_x(character::dir == LEFT && character::action1 != STAND && character::action2 != IDLE && attack);
		kir.reset_src_x(character::dir == RIGHT && character::action1 != STAND && character::action2 != IDLE && attack);
		kwl.reset_src_x(character::dir == LEFT && character::action1 != STAND && character::action2 != MOVE);
		kwr.reset_src_x(character::dir == RIGHT && character::action1 != STAND && character::action2 != MOVE);
		kjl.reset_src_x(character::dir == LEFT && character::action1 != JUMP);
		kjr.reset_src_x(character::dir == RIGHT && character::action1 != JUMP);
		kfl.reset_src_x(character::dir == LEFT && character::action1 != FALL);
		kfr.reset_src_x(character::dir == RIGHT && character::action1 != FALL);
		kwbl.reset_src_x(character::dir == LEFT && character::action1 != STAND && character::action2 != IDLE && !attack && klonoa_mode != NORMAL);
		kwbr.reset_src_x(character::dir == RIGHT && character::action1 != STAND && character::action2 != IDLE && !attack && klonoa_mode != NORMAL);
		kwcl.reset_src_x(character::dir == LEFT && character::action1 != STAND && character::action2 != IDLE && !attack && klonoa_mode != SAMURAI);
		kwcr.reset_src_x(character::dir == RIGHT && character::action1 != STAND && character::action2 != IDLE && !attack && klonoa_mode != SAMURAI);
		wbl.reset_src_x(character::dir == LEFT && !attack && klonoa_mode != NORMAL);
		wbr.reset_src_x(character::dir == RIGHT && !attack && klonoa_mode != NORMAL);
		wcl.reset_src_x(character::dir == LEFT && !attack && klonoa_mode != SAMURAI);
		wcr.reset_src_x(character::dir == RIGHT && !attack && klonoa_mode != SAMURAI);

		vil.reset_src_x(character::dir == LEFT && character::action1 != STAND && character::action2 != IDLE && attack);
		vir.reset_src_x(character::dir == RIGHT && character::action1 != STAND && character::action2 != IDLE && attack);
		vwl.reset_src_x(character::dir == LEFT && character::action1 != STAND && character::action2 != MOVE);
		vwr.reset_src_x(character::dir == RIGHT && character::action1 != STAND && character::action2 != MOVE);
		vjl.reset_src_x(character::dir == LEFT && character::action1 != JUMP);
		vjr.reset_src_x(character::dir == RIGHT && character::action1 != JUMP);
		vfl.reset_src_x(character::dir == LEFT && character::action1 != FALL);
		vfr.reset_src_x(character::dir == RIGHT && character::action1 != FALL);
		vkl.reset_src_x(character::dir == LEFT && character::action1 != STAND && character::action2 != IDLE && !attack);
		vkr.reset_src_x(character::dir == RIGHT && character::action1 != STAND && character::action2 != IDLE && !attack);
		kl.reset_src_x(character::dir == LEFT && !attack);
		kr.reset_src_x(character::dir == RIGHT && !attack);

		wsl.reset_src_x(character::dir == LEFT && character::action1 != STAND && character::action2 != IDLE && !attack);
		wsr.reset_src_x(character::dir == RIGHT && character::action1 != STAND && character::action2 != IDLE && !attack);
		wsjl.reset_src_x(character::dir == LEFT && character::action1 != JUMP);
		wsjr.reset_src_x(character::dir == RIGHT && character::action1 != JUMP);
		wsfl.reset_src_x(character::dir == LEFT && character::action1 != FALL);
		wsfr.reset_src_x(character::dir == RIGHT && character::action1 != FALL);
	};



	auto update_pos = [&] () -> void {
		if (character::action1 == FALL)
			move_down();

		else if (character::action1 == JUMP)
			move_up();



		if (character::action2 == MOVE) {
			if (character::dir == LEFT)
				move_left(current_character);

			else
				move_right(current_character);

		}



		current_sprite->change_pos(character::x, character::y);
		if (character::dir == LEFT)
			current_attack->change_pos(character::x - character::w, character::y);

		else
			current_attack->change_pos(character::x, character::y);



		if (klonoa_mode == SAMURAI && current_ws_sprite != nullptr) {
			current_ws_sprite->change_pos(character::x, character::y);

			if (!attack && character::action1 == STAND && character::action2 == IDLE && current_ws_sprite->get_src_x_index() > 1)
				current_ws_sprite->change_pos(character::x - character::w, character::y);

		}

	};



	auto draw_scenario = [&] () -> void {
		SDL_Rect rec;
		rec.w = background->get_des_w();
		rec.h = background->get_des_h();
		int bgw, bgh;

		SDL_GetWindowSize(win.get_win(), &bgw, &bgh);
		background->change_size(bgw, bgh);
		background->draw();
		background->change_size(rec.w, rec.h);

		for (unsigned int i = 0; i < object::textures.size(); ++i) {
			
			if (object::textures[i] != nullptr) {
				rec = { object::textures[i]->get_des_x(), object::textures[i]->get_des_y(), object::textures[i]->get_des_w(), object::textures[i]->get_des_h() };
				object::textures[i]->change_pos(object::pos[i].first.first, object::pos[i].first.second);
				object::textures[i]->change_size(object::pos[i].second.first - object::pos[i].first.first, object::pos[i].second.second - object::pos[i].first.second);
				object::textures[i]->draw();
				object::textures[i]->change_pos(rec.x, rec.y);
				object::textures[i]->change_size(rec.w, rec.h);

			}

		}
	};

	auto draw_character = [&] () -> void {
		current_sprite->draw();
		if (attack)
			current_attack->draw();

		if (current_character == &klonoa && current_ws_sprite != nullptr && klonoa_mode == SAMURAI)
			current_ws_sprite->draw();

	};



	SDL_Event evn;



	while (!game_over) {

		while (SDL_PollEvent(&evn))
			if (evn.type == SDL_QUIT)
				game_over = true;


		update_actions();
		update_sprites();
		update_pos();

		win.clear(0, 0, 0);
		draw_scenario();
		draw_character();
		win.update();

		SDL_Delay(delay);

	}

	IMG_Quit();
	SDL_Quit();
	return 0;
}