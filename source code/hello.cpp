// compiler comand: g++ hello.cpp -o hello $(pkg-config allegro-5 allegro_image-5 --libs --cflags)

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>



#define W 500
#define H 500

#define PRINT(txt) std::cout << txt;

#define COLOR(r, g, b) al_map_rgb(r, g, b)

#define FPS 15.0f



int x = 250, y = 200;

bool game_over = false;



enum { KLONOA, VANDA } actual_character = KLONOA;



void reset_sources();
void switch_character();



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
	attack_source = source(-32, 0, 32, 32),
	*player_source = &idle_source;



//--------------------------------------------------------------------



int main(int argc, char* argv[]) {
	PRINT("--- starting game ---\n\n")

	al_init();
	al_init_image_addon();
	al_install_keyboard();

	ALLEGRO_DISPLAY* window = NULL;
	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	window = al_create_display(W, H);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0f / FPS);

	ALLEGRO_KEYBOARD_STATE key;

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
	ALLEGRO_BITMAP** attack_sprite;

	al_register_event_source(queue, al_get_display_event_source(window));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());

	al_set_window_title(window, "Klonoa Dimensions - Cheesai Island");



	int jump_count = -1;



	enum { IDLE, MOVE, JUMP, FALL, ATTACK } action1 = IDLE, action2 = IDLE, action3 = IDLE;
	enum { LEFT, RIGHT } dir = RIGHT;
	enum { NORMAL, SAMURAI } klonoa_mode;



	auto update_dir_actions_and_source = [&] () -> void {
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



		if (al_key_down(&key, ALLEGRO_KEY_X)) {
			action3 = ATTACK;
			
			if (player_source == &idle_source)
				player_source = &attack_source;
			
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

	auto update_source_pos = [&] () -> void {
		if (action1 == FALL) {
			if (player_source->get_sx() / 32 < 4)
				player_source->add_sx(32);

			else if (actual_source->get_sx() / 32 > 4)
				player_source->set_sx(0);

		} else if (action1 == JUMP) {
			if (player_source->get_sx() / 32 < 5)
				player_source->add_sx(32);

			else if (actual_source->get_sx() / 32 > 5)
				player_source->set_sx(0);

		} else if (action2 == MOVE) {
			if (player_source->get_sx() / 32 < 3)
				player_source->add_sx(32);

			else
				player_source->set_sx(0);

		} else if (action3 == ATTACK) {
			if (player_source->get_sx() / 64 < 10)
				player_source->add_sx(64);

		} else {
			if (player_source->get_sx() / 32 < 21)
				player_source->add_sx(32);

			else
				player_source->set_sx(0);

		}

	};

	auto update_klonoa_sprite = [&] () -> void {
		if (action1 == FALL) {
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

		} else if (action3 == ATTACK) {
			if (dir == LEFT)
				player_sprite = &kwbl;

			else
				player_sprite = &kwbr;

		} else {
			if (dir == LEFT)
				player_sprite = &kil;

			else
				player_sprite = &kir;

		}

		al_convert_mask_to_alpha(*player_sprite, COLOR(0, 255, 0));
	};

	al_start_timer(timer);

	while (!game_over) {

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			al_get_keyboard_state(&key);
			
			update_dir_actions_and_source();
			update_pos();
			update_source_pos();
			reset_sources();

			if (actual_character == KLONOA)
				update_klonoa_sprite();
	


			if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
				game_over = true;

		} else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_over = true;

		al_clear_to_color(COLOR(12, 24, 52));
		al_draw_bitmap_region(*player_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x, y, 0);
		al_flip_display();
	
	}



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
}



//--------------------------------------------------------------------



void reset_sources() {
	if (player_source == &move_source) {
		idle_source.set_sx(-32);
		idle_source.set_sy(0);
		
		jump_source.set_sx(-32);
		jump_source.set_sy(0);
		
		fall_source.set_sx(-32);
		fall_source.set_sy(0);
		
		attack_source.set_sx(-32);
		attack_source.set_sy(0);

	} else if (player_source == &jump_source) {
		idle_source.set_sx(-32);
		idle_source.set_sy(0);
		
		move_source.set_sx(-32);
		move_source.set_sy(0);
		
		fall_source.set_sx(-32);
		fall_source.set_sy(0);
		
		attack_source.set_sx(-32);
		attack_source.set_sy(0);

	} else if (player_source == &fall_source) {
		idle_source.set_sx(-32);
		idle_source.set_sy(-32);
		
		move_source.set_sx(-32);
		move_source.set_sy(0);
		
		jump_source.set_sx(-32);
		jump_source.set_sy(0);
		
		attack_source.set_sx(-32);
		attack_source.set_sy(0);

	} else if (player_source == &attack_source) {
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
		
		attack_source.set_sx(-32);
		attack_source.set_sy(0);
	
	}

}

void switch_character() {
	if (actual_character == KLONOA)
		actual_character = VANDA;

	else
		actual_character = KLONOA;

}