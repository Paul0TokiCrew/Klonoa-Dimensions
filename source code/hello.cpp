// Compiler comand: g++ hello.cpp -o hello $(pkg-config allegro-5 allegro_image-5 --libs --cflags)

// Headers -----------------------

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

// -------------------------------



// Macros ------------------------

#define W 500
#define H 500

#define PRINT(txt) std::cout << txt;

#define COLOR(r, g, b) al_map_rgb(r, g, b)

#define FPS 15.0f

// -------------------------------



// Global variables --------------

int x = 250, y = 200,
	jump_count = -1,
	jump_height = 9,
	speed = 5;

bool game_over = false,
	attack = false,
	jump_many_times = true;

// -------------------------------



// Global enums ------------------

enum { IDLE, MOVE, JUMP, FALL, ATTACK } action1 = IDLE, action2 = IDLE;
enum { LEFT, RIGHT } dir = RIGHT;
enum { NORMAL, SAMURAI } klonoa_mode = NORMAL;
enum { KLONOA, VANDA } actual_character = KLONOA;

// -------------------------------



// Functions declaration ---------

void update_fall();
void update_jump();
void update_move_left();
void update_move_right();

void reset_sources();
void switch_character();

// -------------------------------



// Classes -----------------------

class source {
private:
	mutable int sx, sy;
	const int sw, sh;

public:
	source(int sx, int sy, int sw, int sh) : sx(sx), sy(sy), sw(sw), sh(sh) { }
	~source() { delete this; }

	void set_sx(int sx) const { this->sx = sx; }
	void set_sy(int sy) const { this->sx = sy; }

	int get_sx() const { return this->sx; }
	int get_sy() const { return this->sy; }
	int get_sw() const { return this->sw; }
	int get_sh() const { return this->sh; }

	void add_sx(int add) const { this->sx += add; }
	void add_sy(int add) const { this->sy += add; }
	
}	idle_source = source(-32, 0, 32, 32),
	move_source = source(-32, 0, 32, 32),
	jump_source = source(-32, 0, 32, 32),
	fall_source = source(-32, 0, 32, 32),
	player_attack_source = source(-32, 0, 32, 32),
	*player_source = &idle_source,
	
	wind_bullet_source = source(-64, 0, 64, 32),
	wind_cut_source = source(-32, 0, 32, 32),
	kick_source = source(-64, 0, 64, 32),
	*attack_source = &wind_bullet_source;



class _player_source {
private:
	mutable int sx, sy;
	const int sw, sh,
		sx_lim, sy_lim,
		action,
		character;

public:
	_player_source(const int sx, const int sy, const int sx_lim, const int sy_lim, const int sw, const int sh, const int action, const int character = 2) :
	sx(sx), sy(sy), sx_lim(sx_lim - 1), sy_lim(sy_lim - 1), sw(sw), sh(sh), action(action), character(character) { }
	~_player_source() { delete this; }
	
	const int get_sx() const { return this->sx; }
	const int get_sy() const { return this->sy; }
	const int get_sw() const { return this->sw; }
	const int get_sh() const { return this->sh; }
	const int get_sx_lim() const { return this->sx_lim; }
	const int get_sy_lim() const { return this->sy_lim; }
	const int get_action() const { return this->action; }
	const int get_character() const { return this->character; }

	const int get_sx_index() const { return this->sx / this->sw; }
	const int get_sy_index() const { return this->sy / this->sh; }
	
	const bool check_actual_character() const;
	const bool check_actual_action(int) const;

	const void update_sx(int) const;
	const void update_sy(int) const;

};

// -------------------------------



// main function --------------------------------------------------------------------



int main(int argc, char* argv[]) {
	// Game start ----------------------

	PRINT("--- starting game ---\n\n")

	al_init();
	al_init_image_addon();
	al_install_keyboard();

	// ---------------------------------



	// Game pointers -------------------
	
	ALLEGRO_DISPLAY* window = NULL;
	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	window = al_create_display(W, H);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0f / FPS);

	// ---------------------------------



	// Keyboard state variable ---------

	ALLEGRO_KEYBOARD_STATE key;

	// ---------------------------------



	// Sprites -------------------------
	
	ALLEGRO_BITMAP* kil = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Idle Left.png");
	ALLEGRO_BITMAP* kir = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Idle Right.png");
	ALLEGRO_BITMAP* kwl = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Walk Left.png");
	ALLEGRO_BITMAP* kwr = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Walk Right.png");
	ALLEGRO_BITMAP* kjl = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Jump Left.png");
	ALLEGRO_BITMAP* kjr = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Jump Right.png");
	ALLEGRO_BITMAP* kfl = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Fall Left.png");
	ALLEGRO_BITMAP* kfr = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Fall Right.png");
	ALLEGRO_BITMAP* kwbl = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Wind Bullet Left.png");
	ALLEGRO_BITMAP* kwbr = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Wind Bullet Right.png");
	ALLEGRO_BITMAP* kwcl = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Wind Cut Left.png");
	ALLEGRO_BITMAP* kwcr = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Wind Cut Right.png");
	ALLEGRO_BITMAP* vil = al_load_bitmap("../sprites/Vanda/Character/Vanda Idle Left.png");
	ALLEGRO_BITMAP* vir = al_load_bitmap("../sprites/Vanda/Character/Vanda Idle Right.png");
	ALLEGRO_BITMAP* vwl = al_load_bitmap("../sprites/Vanda/Character/Vanda Walk Left.png");
	ALLEGRO_BITMAP* vwr = al_load_bitmap("../sprites/Vanda/Character/Vanda Walk Right.png");
	ALLEGRO_BITMAP* vjl = al_load_bitmap("../sprites/Vanda/Character/Vanda Jump Left.png");
	ALLEGRO_BITMAP* vjr = al_load_bitmap("../sprites/Vanda/Character/Vanda Jump Right.png");
	ALLEGRO_BITMAP* vfl = al_load_bitmap("../sprites/Vanda/Character/Vanda Fall Left.png");
	ALLEGRO_BITMAP* vfr = al_load_bitmap("../sprites/Vanda/Character/Vanda Fall Right.png");
	ALLEGRO_BITMAP* vkl = al_load_bitmap("../sprites/Vanda/Character/Vanda Kick Left.png");
	ALLEGRO_BITMAP* vkr = al_load_bitmap("../sprites/Vanda/Character/Vanda Kick Right.png");
	ALLEGRO_BITMAP** player_sprite = &kir;

	ALLEGRO_BITMAP* wbl = al_load_bitmap("../sprites/Klonoa/Attacks/Wind Bullet Left.png");
	ALLEGRO_BITMAP* wbr = al_load_bitmap("../sprites/Klonoa/Attacks/Wind Bullet Right.png");
	ALLEGRO_BITMAP* wcl = al_load_bitmap("../sprites/Klonoa/Attacks/Wind Cut Left.png");
	ALLEGRO_BITMAP* wcr = al_load_bitmap("../sprites/Klonoa/Attacks/Wind Cut Right.png");
	ALLEGRO_BITMAP* kl = al_load_bitmap("../sprites/Vanda/Attacks/Kick Left.png");
	ALLEGRO_BITMAP* kr = al_load_bitmap("../sprites/Vanda/Attacks/Kick Right.png");
	ALLEGRO_BITMAP** attack_sprite = &wbr;

	ALLEGRO_BITMAP* wsl = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Left.png");
	ALLEGRO_BITMAP* wsr = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Right.png");
	ALLEGRO_BITMAP* wsjl = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Jump Left.png");
	ALLEGRO_BITMAP* wsjr = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Jump Right.png");
	ALLEGRO_BITMAP* wsfl = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Fall Left.png");
	ALLEGRO_BITMAP* wsfr = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Fall Right.png");
	ALLEGRO_BITMAP** sword_sprite = &wsr;

	// ---------------------------------



	// Event sources register ----------

	al_register_event_source(queue, al_get_display_event_source(window));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());

	// ---------------------------------



	// Window title --------------------

	al_set_window_title(window, "Klonoa Dimensions - Cheesai Island");

	// ---------------------------------



	// Sources update ------------------
	
	auto update_attack_source = [&] () -> void {
		if (actual_character == KLONOA) {

			if (klonoa_mode == NORMAL)
				attack_source = &wind_bullet_source;

			else
				attack_source = &wind_cut_source;

		} else
			attack_source = &kick_source;

	};

	auto update_dir_actions_and_sources = [&] () -> void {
		if (al_key_down(&key, ALLEGRO_KEY_Z) && jump_count < jump_height && (action1 != FALL || jump_many_times))
			update_jump();

		else if (jump_count > -1)
			update_fall();
			
		else
			action1 = IDLE;



		if (al_key_down(&key, ALLEGRO_KEY_LEFT))
			update_move_left();

		else if (al_key_down(&key, ALLEGRO_KEY_RIGHT))
			update_move_right();

		else
			action2 = IDLE;



		if (al_key_down(&key, ALLEGRO_KEY_X) || attack) {
			attack = true;
			
			if (player_source == &idle_source || attack)
				player_source = &player_attack_source;
			
			update_attack_source();
			PRINT("attack\n")
		
		} else
			attack = false;



		if (al_key_down(&key, ALLEGRO_KEY_S) && actual_character == KLONOA && !attack) {
			
			if (klonoa_mode == NORMAL) {
				klonoa_mode = SAMURAI;
				PRINT("mode: samurai\n")

			} else {
				klonoa_mode = NORMAL;
				PRINT("mode: normal\n")

			}
		
		}



		if (al_key_down(&key, ALLEGRO_KEY_C) && !attack) {
			switch_character();
			PRINT("character swicthed\n")

		}



		if (action1 == IDLE && action2 == IDLE && !attack)
			player_source = &idle_source;

	};

	// ---------------------------------



	// Position update -----------------
	
	auto update_pos = [&] () -> void {
		if (action1 == FALL)
			y += 10;

		else if (action1 == JUMP)
			y -= 10;



		if (action2 == MOVE)  {
			
			if (dir == LEFT)
				x -= speed;

			else
				x += speed;

		}

	};

	// ---------------------------------



	// Sources position updates --------

	auto update_attack_source_pos = [&] () -> void {
		if (attack) {

			if (actual_character == KLONOA) {

				if (klonoa_mode == NORMAL) {
			
					if (attack_source->get_sx() / 64 < 10)
						attack_source->add_sx(64);

					else
						attack = false;

				} else {
			
					if (attack_source->get_sx() / 32 < 4)
						attack_source->add_sx(32);

					else
						attack = false;

				}

			} else {

				if (attack_source->get_sx() / 64 < 7)
					attack_source->add_sx(64);

				else
					attack = false;

			}
	
		}

	};

	auto update_sources_pos = [&] () -> void {
		if (attack && action1 == IDLE && action2 == IDLE) {

			if (actual_character == KLONOA) {
			
				if (klonoa_mode == NORMAL) {
				
					if (player_source->get_sx() / 32 < 10)
						player_source->add_sx(32);

					else
						player_source->set_sx(0);

				}  else {
				
					if (player_source->get_sx() / 32 < 4)
						player_source->add_sx(32);

					else
						player_source->set_sx(0);

				}

			} else {

				if (player_source->get_sx() / 32 < 3)
					player_source->add_sx(32);

				else
					player_source->set_sx(0);

			}

		} else if (action1 == FALL) {

			if (player_source->get_sx() / 32 < 4)
				player_source->add_sx(32);

			else if (player_source->get_sx() / 32 > 4)
				player_source->set_sx(0);

		} else if (action1 == JUMP) {

			if (player_source->get_sx() / 32 < 5)
				player_source->add_sx(32);

			else if (player_source->get_sx() / 32 > 5)
				player_source->set_sx(0);

		} else if (action2 == MOVE) {

			if (player_source->get_sx() / 32 < 3)
				player_source->add_sx(32);

			else
				player_source->set_sx(0);

		} else {

			if (player_source->get_sx() / 32 < 21)
				player_source->add_sx(32);

			else
				player_source->set_sx(0);

		}

		if (attack)
			update_attack_source_pos();
	
	};

	// ---------------------------------

	

	// Sprites updates -----------------

	auto update_attack_sprite = [&] () -> void {
		if (attack) {

			if (actual_character == KLONOA) {

				if (klonoa_mode == NORMAL) {

					if (dir == LEFT)
						attack_sprite = &wbl;

					else
						attack_sprite = &wbr;

				} else {
					
					if (dir == LEFT)
						attack_sprite = &wcl;

					else
						attack_sprite = &wcr;

				}

			} else {

				if (dir == LEFT)
					attack_sprite = &kl;

				else
					attack_sprite = &kr;

			}
		
		}

		al_convert_mask_to_alpha(*attack_sprite, COLOR(0, 255, 0));
	};

	auto update_sword_sprite = [&] () -> void {
		if (actual_character == KLONOA) {
			
			if (klonoa_mode == SAMURAI) {
			
				if (action1 == FALL) {
			
					if (dir == LEFT)
						sword_sprite = &wsfl;

					else
						sword_sprite = &wsfr;

				} else if (action1 == JUMP) {
			
					if (dir == LEFT)
						sword_sprite = &wsjl;

					else
						sword_sprite = &wsjr;


				} else {
			
					if (dir == LEFT)
						sword_sprite = &wsl;

					else
						sword_sprite = &wsr;

				}

			}

		}

		al_convert_mask_to_alpha(*sword_sprite, COLOR(0, 255, 0));	
	};

	auto update_sprites = [&] () -> void {
		if (actual_character == KLONOA) {

			if (attack && action1 == IDLE && action2 == IDLE) {

				if (klonoa_mode == NORMAL) {

					if (dir == LEFT)
						player_sprite = &kwbl;

					else
						player_sprite = &kwbr;

				} else {

					if (dir == LEFT)
						player_sprite = &kwcl;

					else
						player_sprite = &kwcr;

				}

			} else if (action1 == FALL) {

				if (dir == LEFT)
					player_sprite = &kfl;

				else
					player_sprite = &kfr;
		
			} else if (action1 == JUMP) {
				
				if (dir == LEFT)
					player_sprite = &kjl;

				else
					player_sprite = &kjr;

			} else if (action2 == MOVE) {

				if (dir == LEFT)
					player_sprite = &kwl;

				else
					player_sprite = &kwr;

			} else {

				if (dir == LEFT)
					player_sprite = &kil;

				else
					player_sprite = &kir;
			}

			if (klonoa_mode == SAMURAI && !attack)
				update_sword_sprite();

		} else {

			if (attack && action1 == IDLE && action2 == IDLE) {

				if (dir == LEFT)
					player_sprite = &vkl;
				
				else
					player_sprite = &vkr;

			} else if (action1 == FALL) {

				if (dir == LEFT)
					player_sprite = &vfl;

				else
					player_sprite = &vfr;

			} else if (action1 == JUMP) {
				
				if (dir == LEFT)
					player_sprite = &vjl;

				else
					player_sprite = &vjr;
				
			} else if (action2 == MOVE) {
				
				if (dir == LEFT)
					player_sprite = &vwl;

				else
					player_sprite = &vwr;

			} else {
				
				if (dir == LEFT)
					player_sprite = &vil;

				else
					player_sprite = &vir;

			}

		}

		if (attack)
			update_attack_sprite();
	
		al_convert_mask_to_alpha(*player_sprite, COLOR(0, 255, 0));
	};

	// ---------------------------------



	// Drawing -------------------------

	auto draw_attack = [&] () -> void {
		al_set_target_bitmap(al_get_backbuffer(window));

		if (attack) {

			if (actual_character == KLONOA) {

				if (klonoa_mode == NORMAL) {

					if (dir == LEFT)
						al_draw_bitmap_region(*attack_sprite, attack_source->get_sx(), attack_source->get_sy(), attack_source->get_sw(), attack_source->get_sh(), x - 32, y, 0);

					else
						al_draw_bitmap_region(*attack_sprite, attack_source->get_sx(), attack_source->get_sy(), attack_source->get_sw(), attack_source->get_sh(), x, y, 0);

				} else {

					if (dir == LEFT)
						al_draw_bitmap_region(*attack_sprite, attack_source->get_sx(), attack_source->get_sy(), attack_source->get_sw(), attack_source->get_sh(), x - 9 - 4, y, 0);

					else
						al_draw_bitmap_region(*attack_sprite, attack_source->get_sx(), attack_source->get_sy(), attack_source->get_sw(), attack_source->get_sh(), x + 4, y, 0);

				}
			
			} else {

				if (dir == LEFT)
					al_draw_bitmap_region(*attack_sprite, attack_source->get_sx(), attack_source->get_sy(), attack_source->get_sw(), attack_source->get_sh(), x - 32, y, 0);

				else
					al_draw_bitmap_region(*attack_sprite, attack_source->get_sx(), attack_source->get_sy(), attack_source->get_sw(), attack_source->get_sh(), x, y, 0);

			}

		}

	};

	auto draw_sword = [&] () -> void {
		al_set_target_bitmap(al_get_backbuffer(window));

		if (actual_character == KLONOA && klonoa_mode == SAMURAI) {

			if (action1 == FALL) {

				if (dir == LEFT)
					al_draw_bitmap_region(*sword_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x - 9, y, 0);

				else
					al_draw_bitmap_region(*sword_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x, y, 0);

			} else if (action1 == JUMP) {
				
				if (dir == LEFT)
					al_draw_bitmap_region(*sword_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x - 9, y, 0);
				
				else
					al_draw_bitmap_region(*sword_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x, y, 0);

			} else if (action2 == MOVE) {

				if (dir == LEFT) {
		
					if (player_source->get_sx() / 32 < 2)
						al_draw_bitmap(*sword_sprite, x - 9, y, 0);

					else
						al_draw_bitmap(*sword_sprite, x - 9 - 2, y, 0);

				} else {
			
					if (player_source->get_sx() / 32 < 2)
						al_draw_bitmap(*sword_sprite, x, y, 0);

					else
						al_draw_bitmap(*sword_sprite, x - 2, y, 0);

				}

			} else {

				if (dir == LEFT)
					al_draw_bitmap(*sword_sprite, x - 9, y, 0);

				else
					al_draw_bitmap(*sword_sprite, x, y, 0);

			}

		}

	};

	// ---------------------------------



	// Game loop -----------------------

	al_start_timer(timer);

	while (!game_over) {

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			al_get_keyboard_state(&key);
			
			update_dir_actions_and_sources();
			update_pos();
			update_sources_pos();
			reset_sources();
			update_sprites();

			if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
				game_over = true;

		} else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_over = true;

		al_clear_to_color(COLOR(12, 24, 52));

		

		if (attack && dir == LEFT)
			draw_attack();

		else if (klonoa_mode == SAMURAI && dir == LEFT)
			draw_sword();



		al_draw_bitmap_region(*player_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x, y, 0);
		


		if (attack && dir == RIGHT)
			draw_attack();

		else if (klonoa_mode == SAMURAI && dir == RIGHT)
			draw_sword();

		al_flip_display();
	
	}

	// ---------------------------------



	// Game end ------------------------

	al_destroy_display(window);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_destroy_bitmap(kil);
	al_destroy_bitmap(kir);
	al_destroy_bitmap(kwl);
	al_destroy_bitmap(kwr);
	al_destroy_bitmap(kjl);
	al_destroy_bitmap(kjr);
	al_destroy_bitmap(kfl);
	al_destroy_bitmap(kfr);
	al_destroy_bitmap(kwbl);
	al_destroy_bitmap(kwbr);
	al_destroy_bitmap(wbl);
	al_destroy_bitmap(wbr);

	PRINT("\n--- game over ---\n\n")
	return 0;

	// ---------------------------------

}



// ----------------------------------------------------------------------------------



// Functions definition ----------

void update_fall() {
	if (jump_count > -1) {
		action1 = FALL;
		player_source = &fall_source;
		jump_count--;
		PRINT("fall\n")
	
	} else
		action1 = IDLE;

}

void update_jump() {
	if (jump_count < jump_height && (action1 != FALL || jump_many_times)) {
		action1 = JUMP;
		player_source = &jump_source;	
		jump_count++;
		PRINT("jump\n")

	} else
		action1 = FALL;

}

void update_move_left() {
	dir = LEFT;
	action2 = MOVE;

	if (player_source == &idle_source)
		player_source = &move_source;
			
	PRINT("move left\n")
}

void update_move_right() {
	dir = RIGHT;
		action2 = MOVE;
			
	if (player_source == &idle_source)
		player_source = &move_source;
			
	PRINT("move right\n")
}



void reset_sources() {
	if (!attack) {
		wind_bullet_source.set_sx(-32);
		wind_bullet_source.set_sy(0);

		wind_cut_source.set_sx(-32);
		wind_cut_source.set_sy(0);

		kick_source.set_sx(-32);
		kick_source.set_sy(0);
}



	if (player_source == &move_source) {
		idle_source.set_sx(-32);
		idle_source.set_sy(0);
		
		jump_source.set_sx(-32);
		jump_source.set_sy(0);
		
		fall_source.set_sx(-32);
		fall_source.set_sy(0);
		
		player_attack_source.set_sx(-32);
		player_attack_source.set_sy(0);

	} else if (player_source == &jump_source) {
		idle_source.set_sx(-32);
		idle_source.set_sy(0);
		
		move_source.set_sx(-32);
		move_source.set_sy(0);
		
		fall_source.set_sx(-32);
		fall_source.set_sy(0);
		
		player_attack_source.set_sx(-32);
		player_attack_source.set_sy(0);

	} else if (player_source == &fall_source) {
		idle_source.set_sx(-32);
		idle_source.set_sy(-32);
		
		move_source.set_sx(-32);
		move_source.set_sy(0);
		
		jump_source.set_sx(-32);
		jump_source.set_sy(0);
		
		player_attack_source.set_sx(-32);
		player_attack_source.set_sy(0);

	} else if (player_source == &player_attack_source) {
		idle_source.set_sx(-32);
		idle_source.set_sy(0);
		
		move_source.set_sx(-32);
		move_source.set_sy(0);

		jump_source.set_sx(-32);
		jump_source.set_sy(0);
		
		fall_source.set_sx(-32);
		fall_source.set_sy(0);

	} else {
		move_source.set_sx(-32);
		move_source.set_sy(0);
		
		jump_source.set_sx(-32);
		jump_source.set_sy(0);
		
		fall_source.set_sx(-32);
		fall_source.set_sy(0);
		
		player_attack_source.set_sx(-32);
		player_attack_source.set_sy(0);
	
	}

}

void switch_character() {
	if (actual_character == KLONOA) {
		actual_character = VANDA;
		jump_height = 5;
		jump_many_times = false;
		speed = 7;

	} else {
		actual_character = KLONOA;
		jump_height = 12;
		jump_many_times = true;
		speed = 5;

	}

}

// -------------------------------



// Methods definition ------------

const bool _player_source::check_actual_character() const {
	if (actual_character == this->character)
		return true;

	else
		return false;

}

const bool _player_source::check_actual_action(int action_n) const {
	if (action_n == 1) {

		if (action1 == this->action)
			return true;

		else
			return false;

	} else {

		if (action2 == this->action)
			return true;

		else
			return false;
	
	}

}

const void _player_source::update_sx(int action_n) const {
	if ((this->character == 2 || this->check_actual_character()) && this->check_actual_action(action_n)) {

		if (this->get_sx_index() < this->sx_lim)
			this->sx += this->sw;

		else
			this->sx = 0;
	
	}

}

const void _player_source::update_sy(int action_n) const {
	if ((this->character == 2 || this->check_actual_character()) && this->check_actual_action(action_n)) {

		if (this->get_sx_index() < this->sy_lim)
			this->sy += this->sh;

		else
			this->sy = 0;
	
	}

}

// -------------------------------