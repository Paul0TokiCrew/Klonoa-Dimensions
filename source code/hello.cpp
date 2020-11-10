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

int x = 250, y = 200;
int jump_count = -1;
bool game_over = false, attack = false;

// -------------------------------



// Global enums ------------------

enum { KLONOA, VANDA } actual_character = KLONOA;

// -------------------------------



// Functions declaration ---------

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
	*attack_source = &wind_bullet_source;

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
	
	ALLEGRO_BITMAP* kil = al_load_bitmap("../sprites/Klonoa Idle Left.png");
	ALLEGRO_BITMAP* kir = al_load_bitmap("../sprites/Klonoa Idle Right.png");
	ALLEGRO_BITMAP* kwl = al_load_bitmap("../sprites/Klonoa Walk Left.png");
	ALLEGRO_BITMAP* kwr = al_load_bitmap("../sprites/Klonoa Walk Right.png");
	ALLEGRO_BITMAP* kjl = al_load_bitmap("../sprites/Klonoa Jump Left.png");
	ALLEGRO_BITMAP* kjr = al_load_bitmap("../sprites/Klonoa Jump Right.png");
	ALLEGRO_BITMAP* kfl = al_load_bitmap("../sprites/Klonoa Fall Left.png");
	ALLEGRO_BITMAP* kfr = al_load_bitmap("../sprites/Klonoa Fall Right.png");
	ALLEGRO_BITMAP* kwbl = al_load_bitmap("../sprites/Klonoa Wind Bullet Left.png");
	ALLEGRO_BITMAP* kwbr = al_load_bitmap("../sprites/Klonoa Wind Bullet Right.png");
	ALLEGRO_BITMAP** player_sprite = &kir;

	ALLEGRO_BITMAP* wbl = al_load_bitmap("../sprites/Wind Bullet Left.png");
	ALLEGRO_BITMAP* wbr = al_load_bitmap("../sprites/Wind Bullet Right.png");
	ALLEGRO_BITMAP** attack_sprite = &wbr;

	ALLEGRO_BITMAP* wsl = al_load_bitmap("../sprites/Wind Sword Left.png");
	ALLEGRO_BITMAP* wsr = al_load_bitmap("../sprites/Wind Sword Right.png");
	ALLEGRO_BITMAP* wsjl = al_load_bitmap("../sprites/Wind Sword Jump Left.png");
	ALLEGRO_BITMAP* wsjr = al_load_bitmap("../sprites/Wind Sword Jump Right.png");
	ALLEGRO_BITMAP* wsfl = al_load_bitmap("../sprites/Wind Sword Fall Left.png");
	ALLEGRO_BITMAP* wsfr = al_load_bitmap("../sprites/Wind Sword Fall Right.png");
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



	// Local enums ---------------------

	enum { IDLE, MOVE, JUMP, FALL, ATTACK } action1 = IDLE, action2 = IDLE, action3 = IDLE;
	enum { LEFT, RIGHT } dir = RIGHT;
	enum { NORMAL, SAMURAI } klonoa_mode = NORMAL;

	// ---------------------------------



	// Sources update ------------------
	
	auto update_attack_source = [&] () -> void {
		if (actual_character == KLONOA) {
			if (klonoa_mode == NORMAL)
				attack_source = &wind_bullet_source;

		} else {

		}

	};

	auto update_dir_actions_and_sources = [&] () -> void {
		if (al_key_down(&key, ALLEGRO_KEY_Z) && jump_count < 9) {
			action1 = JUMP;
			
			if (player_source == &idle_source)
				player_source = &jump_source;
			
			jump_count++;
			PRINT("jump\n")
		
		} else if (jump_count > -1) {
			action1 = FALL;
			jump_count--;
			
			if (player_source == &jump_source)
				player_source = &fall_source;

			PRINT("fall\n")

		} else
			action1 = IDLE;



		if (al_key_down(&key, ALLEGRO_KEY_LEFT)) {
			dir = LEFT;
			action2 = MOVE;
			
			if (player_source == &idle_source)
				player_source = &move_source;
			
			PRINT("move left\n")

		} else if (al_key_down(&key, ALLEGRO_KEY_RIGHT)) {
			dir = RIGHT;
			action2 = MOVE;
			
			if (player_source == &idle_source)
				player_source = &move_source;
			
			PRINT("move right\n")

		} else
			action2 = IDLE;



		if (al_key_down(&key, ALLEGRO_KEY_X) || attack) {
			attack = true;
			
			if (player_source == &idle_source || attack) {
				player_source = &player_attack_source;
				action3 = ATTACK;

			}
			
			update_attack_source();
			PRINT("attack\n")
		
		} else
			action3 = IDLE;



		if (al_key_down(&key, ALLEGRO_KEY_S)) {
			if (klonoa_mode == NORMAL) {
				klonoa_mode = SAMURAI;
				PRINT("mode: samurai\n")

			} else {
				klonoa_mode = NORMAL;
				PRINT("mode: normal\n")

			}
		
		}



		if (al_key_down(&key, ALLEGRO_KEY_C)) {
			switch_character();
			PRINT("character swicthed\n")

		}



		if (action1 == IDLE && action2 == IDLE && action3 == IDLE)
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
				x -= 5;

			else
				x += 5;

		}

	};

	// ---------------------------------



	// Sources position updates --------

	auto update_attack_source_pos = [&] () -> void {
		if (attack) {
			if (attack_source->get_sx() / 64 < 10)
				attack_source->add_sx(64);

			else
				attack = false;
	
		}

	};

	auto update_sources_pos = [&] () -> void {
		if (action3 == ATTACK && action1 == IDLE && action2 == IDLE) {
			if (player_source->get_sx() / 32 < 10)
				player_source->add_sx(32);

			else
				player_source->set_sx(0);

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

				}

			} else {

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


				} else if (action3 == IDLE) {
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
			if (action3 == ATTACK && action1 == IDLE && action2 == IDLE) {
				if (dir == LEFT)
					player_sprite = &kwbl;

				else
					player_sprite = &kwbr;

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

			if (klonoa_mode == SAMURAI)
				update_sword_sprite();

		} else {

		}

		if (attack)
			update_attack_sprite();
	
		al_convert_mask_to_alpha(*player_sprite, COLOR(0, 255, 0));
	};

	// ---------------------------------



	// Drawing -------------------------

	auto draw = [&] () -> void {
		al_set_target_bitmap(al_get_backbuffer(window));
		al_clear_to_color(COLOR(12, 24, 52));

		if (attack && dir == LEFT)
			al_draw_bitmap_region(*attack_sprite, attack_source->get_sx(), attack_source->get_sy(), attack_source->get_sw(), attack_source->get_sh(), x - 32, y, 0);

		if (actual_character == KLONOA && klonoa_mode == SAMURAI && dir == LEFT) {
			if (action1 == FALL)
				al_draw_bitmap_region(*sword_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x - 9, y, 0);
			
			else if (action1 == JUMP)
				al_draw_bitmap_region(*sword_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x - 9, y, 0);

			else if (action2 == MOVE) {
				if (player_source->get_sx() / 32 < 2)
					al_draw_bitmap(*sword_sprite, x - 9, y, 0);

				else
					al_draw_bitmap(*sword_sprite, x - 9 - 2, y, 0);

			} else
				al_draw_bitmap(*sword_sprite, x - 9, y, 0);

		}

		

		al_draw_bitmap_region(*player_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x, y, 0);
		


		if (attack && dir == RIGHT)
			al_draw_bitmap_region(*attack_sprite, attack_source->get_sx(), attack_source->get_sy(), attack_source->get_sw(), attack_source->get_sh(), x, y, 0);

		if (actual_character == KLONOA && klonoa_mode == SAMURAI && dir == RIGHT) {
			if (action1 == FALL)
				al_draw_bitmap_region(*sword_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x, y, 0);
			
			else if (action1 == JUMP)
				al_draw_bitmap_region(*sword_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x, y, 0);

			else if (action2 == MOVE) {
				if (player_source->get_sx() / 32 < 2)
					al_draw_bitmap(*sword_sprite, x, y, 0);

				else
					al_draw_bitmap(*sword_sprite, x - 2, y, 0);

			} else
				al_draw_bitmap(*sword_sprite, x, y, 0);

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

		draw();
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

void reset_sources() {
	if (!attack) {
		wind_bullet_source.set_sx(-32);
		wind_bullet_source.set_sy(0);
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
	if (actual_character == KLONOA)
		actual_character = VANDA;

	else
		actual_character = KLONOA;

}

// -------------------------------