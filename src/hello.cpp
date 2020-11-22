// Compiler comand: g++ hello.cpp -o ../bin/hello $(pkg-config allegro-5 allegro_image-5 allegro_primitives-5 --libs --cflags)

// Headers -----------------------

#include <iostream>
#include <vector>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

// -------------------------------



// Macros ------------------------

#define W 500
#define H 500

#define PRINT(txt) std::cout << txt;

#define COLOR(r, g, b) al_map_rgb(r, g, b)

#define FPS 15.0f

#define ATTACK -1

// -------------------------------



// Global variables --------------

int x = 250, y = 200,
	jump_count = -1,
	jump_height = 9,
	speed = 5,
	switch_count = 0;

bool game_over = false,
	attack = false,
	jump_many_times = true;

std::vector<std::pair<int, int> > x_pos;

// -------------------------------



// Global enums ------------------

enum { IDLE, MOVE, JUMP, FALL } action1 = IDLE, action2 = IDLE;
enum { LEFT, RIGHT } dir = RIGHT;
enum { NORMAL, SAMURAI } klonoa_mode = NORMAL;
enum { KLONOA, VANDA } actual_character = KLONOA;

// -------------------------------



// Prototypes --------------------

const void switch_character();
const void add_to_map(const int, const int);
const bool check_x_collision();

// -------------------------------



// Classes -----------------------

class source {
protected:
	mutable int sx, sy;
	const int sw, sh,
		sx_lim, sy_lim,
		action,
		set_to_0,
		character,
		is_attack;

public:
	constexpr source(const int sx, const int sy, const int sx_lim, const int sy_lim, const int sw, const int sh, const int action, const bool set_to_0 = true, const int character = 2, const int is_attack = false) :
	sx(sx), sy(sy), sx_lim(sx_lim - 1), sy_lim(sy_lim - 1), sw(sw), sh(sh), action(action), set_to_0(set_to_0), character(character), is_attack(is_attack) { }
	~source() { delete this; }

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
	const bool check_actual_action(const int) const;

	virtual const void update_sx(const int) const;
	virtual const void update_sy(const int) const;
	virtual const void update_sx(const int, const int) const;
	virtual const void update_sy(const int, const int) const;

} const idle_source = source(-32, 0, 22, 1, 32, 32, IDLE),
	move_source = source(-32, 0, 4, 1, 32, 32, MOVE),
	fall_source = source(-32, 0, 5, 1, 32, 32, FALL, false),
	jump_source = source(-32, 0, 6, 1, 32, 32, JUMP, false),
	klonoa_wb_source = source(-32, 0, 11, 1, 32, 32, ATTACK, false, KLONOA, true),
	klonoa_wc_source = source(-32, 0, 5, 1, 32, 32, ATTACK, false, KLONOA, true),
	vanda_k_source = source(-32, 0, 8, 1, 32, 32, ATTACK, false, VANDA, true),
	*player_source = &idle_source,

	wind_bullet_source = source(-64, 0, 11, 1, 64, 32, ATTACK, false, KLONOA, true),
	wind_cut_source = source(-64, 0, 5, 1, 64, 32, ATTACK, false, KLONOA, true),
	kick_source = source(-64, 0, 8, 1, 64, 32, ATTACK, false, VANDA, true),
	*attack_source = &wind_bullet_source;



class ws_source : public source {
public:
	constexpr ws_source(const int sx, const int sy, const int sx_lim, const int sy_lim, const int sw, const int sh, const int action, const bool set_to_0 = true, const int is_attack = false) :
	source(sx, sy, sx_lim, sy_lim, sw, sh, action, set_to_0, KLONOA, is_attack) { }
	~ws_source() { delete this; }

	const void update_sx(const int) const override;
	const void update_sy(const int) const override;
	const void update_sx(const int, const int) const override;
	const void update_sy(const int, const int) const override;

} const ws_wind_cut_source = ws_source(-32, 0, 5, 1, 32, 32, ATTACK, false, true),
	ws_fall_source = ws_source(-32, 0, 5, 1, 32, 32, FALL, false),
	ws_jump_source = ws_source(-32, 0, 6, 1, 32, 32, JUMP, false),
	*ws_source = &ws_jump_source;

// -------------------------------



// main function --------------------------------------------------------------------



int main(int argc, char* argv[]) {
	// Game start ----------------------

	PRINT("--- starting game ---\n\n")

	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_keyboard();
	add_to_map(350, 400);
	add_to_map(50, 80);

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
	
	ALLEGRO_BITMAP* kil = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Idle Left.png"),
		* kir = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Idle Right.png"),
		* kwl = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Walk Left.png"),
		* kwr = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Walk Right.png"),
		* kjl = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Jump Left.png"),
		* kjr = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Jump Right.png"),
		* kfl = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Fall Left.png"),
		* kfr = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Fall Right.png"),
		* kwbl = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Wind Bullet Left.png"),
		* kwbr = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Wind Bullet Right.png"),
		* kwcl = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Wind Cut Left.png"),
		* kwcr = al_load_bitmap("../sprites/Klonoa/Character/Klonoa Wind Cut Right.png"),
		* vil = al_load_bitmap("../sprites/Vanda/Character/Vanda Idle Left.png"),
		* vir = al_load_bitmap("../sprites/Vanda/Character/Vanda Idle Right.png"),
		* vwl = al_load_bitmap("../sprites/Vanda/Character/Vanda Walk Left.png"),
		* vwr = al_load_bitmap("../sprites/Vanda/Character/Vanda Walk Right.png"),
		* vjl = al_load_bitmap("../sprites/Vanda/Character/Vanda Jump Left.png"),
		* vjr = al_load_bitmap("../sprites/Vanda/Character/Vanda Jump Right.png"),
		* vfl = al_load_bitmap("../sprites/Vanda/Character/Vanda Fall Left.png"),
		* vfr = al_load_bitmap("../sprites/Vanda/Character/Vanda Fall Right.png"),
		* vkl = al_load_bitmap("../sprites/Vanda/Character/Vanda Kick Left.png"),
		* vkr = al_load_bitmap("../sprites/Vanda/Character/Vanda Kick Right.png"),
		** player_sprite = &kir,

		* wbl = al_load_bitmap("../sprites/Klonoa/Attacks/Wind Bullet Left.png"),
		* wbr = al_load_bitmap("../sprites/Klonoa/Attacks/Wind Bullet Right.png"),
		* wcl = al_load_bitmap("../sprites/Klonoa/Attacks/Wind Cut Left.png"),
		* wcr = al_load_bitmap("../sprites/Klonoa/Attacks/Wind Cut Right.png"),
		* kl = al_load_bitmap("../sprites/Vanda/Attacks/Kick Left.png"),
		* kr = al_load_bitmap("../sprites/Vanda/Attacks/Kick Right.png"),
		** attack_sprite = &wbr,

		* wsl = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Left.png"),
		* wsr = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Right.png"),
		* wsjl = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Jump Left.png"),
		* wsjr = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Jump Right.png"),
		* wsfl = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Fall Left.png"),
		* wsfr = al_load_bitmap("../sprites/Klonoa/Wind Sword/Wind Sword Fall Right.png"),
		** sword_sprite = &wsr;

	// ---------------------------------



	// Event sources register ----------

	al_register_event_source(queue, al_get_display_event_source(window));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());

	// ---------------------------------



	// Window title --------------------

	al_set_window_title(window, "Klonoa Dimensions - Cheesai Island");

	// ---------------------------------



	// General update ------------------


	auto def_sprite = [] (ALLEGRO_BITMAP*& l, ALLEGRO_BITMAP*& r) -> ALLEGRO_BITMAP** {
		if (dir == LEFT)
			return &l;

		else
			return &r;

	};
	
	auto update_dir_and_actions = [&] () -> void {
		if (al_key_down(&key, ALLEGRO_KEY_Z) && jump_count < jump_height && (action1 != FALL || jump_many_times)) {
			action1 = JUMP;
			jump_count++;
			PRINT("jump\n")

		} else if (jump_count > -1) {
			action1 = FALL;
			jump_count--;
			PRINT("fall\n")

		} else
			action1 = IDLE;



		if (al_key_down(&key, ALLEGRO_KEY_LEFT)) {
			dir = LEFT;
			action2 = MOVE;
			PRINT("move left\n")
		
		} else if (al_key_down(&key, ALLEGRO_KEY_RIGHT)) {
			dir = RIGHT;
			action2 = MOVE;
			PRINT("move right\n")

		} else
			action2 = IDLE;



		if (al_key_down(&key, ALLEGRO_KEY_X) || attack) {
			attack = true;
			PRINT("attack\n")
		
		} else
			attack = false;



		if (!switch_count && al_key_down(&key, ALLEGRO_KEY_S) && actual_character == KLONOA && !attack) {
			switch_count = 5;

			if (klonoa_mode == NORMAL) {
				klonoa_mode = SAMURAI;
				PRINT("mode: samurai\n")

			} else {
				klonoa_mode = NORMAL;
				PRINT("mode: normal\n")

			}
		
		}



		if (!switch_count && al_key_down(&key, ALLEGRO_KEY_C) && !attack) {
			switch_count = 5;
			switch_character();
			PRINT("character swicthed\n")

		}



		if (switch_count)
			switch_count--;

	};

	auto update_sources_and_sprites = [&] () -> void {
		if (action1 == FALL) {
			player_source = &fall_source;
			ws_source = &ws_fall_source;
			sword_sprite = def_sprite(wsfl, wsfr);

			if (actual_character == VANDA)
				player_sprite = def_sprite(vfl, vfr);

			else
				player_sprite = def_sprite(kfl, kfr);


		} else if (action1 == JUMP) {
			player_source = &jump_source;
			ws_source = &ws_jump_source;
			sword_sprite = def_sprite(wsjl, wsjr);

			if (actual_character == VANDA)
				player_sprite = def_sprite(vjl, vjr);

			else
				player_sprite = def_sprite(kjl, kjr);

		
		} else if (action2 == MOVE) {
			player_source = &move_source;
			sword_sprite = def_sprite(wsl, wsr);

			if (actual_character == VANDA)
				player_sprite = def_sprite(vwl, vwr);

			else
				player_sprite = def_sprite(kwl, kwr);


		} else {
			player_source = &idle_source;
			sword_sprite = def_sprite(wsl, wsr);

			if (actual_character == VANDA)
				player_sprite = def_sprite(vil, vir);

			else
				player_sprite = def_sprite(kil, kir);


		}
		


		if (attack) {

			if (actual_character == VANDA) {
				attack_source = &kick_source;
				attack_sprite = def_sprite(kl, kr);
				
				if (player_source == &idle_source) {
					player_source = &vanda_k_source;
					player_sprite = def_sprite(vkl, vkr);

				}

			} else if (klonoa_mode == NORMAL) {
				attack_source = &wind_bullet_source;
				attack_sprite = def_sprite(wbl, wbr);
				
				if (player_source == &idle_source) {
					player_source = &klonoa_wb_source;
					player_sprite = def_sprite(kwbl, kwbr);

				}

			} else {
				attack_source = &wind_cut_source;
				attack_sprite = def_sprite(wcl, wcr);
				ws_source = &ws_wind_cut_source;
				
				if (player_source == &idle_source) {
					player_source = &klonoa_wc_source;
					player_sprite = def_sprite(kwcl, kwcr);

				}

			}

		}

		idle_source.update_sx(1, 2);
		move_source.update_sx(2);
		fall_source.update_sx(1);
		jump_source.update_sx(1);
		klonoa_wb_source.update_sx(0);
		klonoa_wc_source.update_sx(0);
		vanda_k_source.update_sx(0);
		wind_bullet_source.update_sx(0);
		wind_cut_source.update_sx(0);
		kick_source.update_sx(0);
		ws_wind_cut_source.update_sx(0);
		ws_fall_source.update_sx(1);
		ws_jump_source.update_sx(1);

		al_convert_mask_to_alpha(*player_sprite, COLOR(0, 255, 0));
		al_convert_mask_to_alpha(*attack_sprite, COLOR(0, 255, 0));
		al_convert_mask_to_alpha(*sword_sprite, COLOR(0, 255, 0));	

	};

	// ---------------------------------



	// Position update -----------------

	auto move_x = [&] () -> void {

		for (int i = 0; i < speed; i++) {

			if(check_x_collision())
				break;

			if (dir == LEFT)
				x--;

			else
				x++;

		}

	};
	
	auto update_pos = [&] () -> void {
		if (action1 == FALL)
			y += 10;

		else if (action1 == JUMP)
			y -= 10;

		

		if (action2 == MOVE)
			move_x();

	};

	// ---------------------------------



	// Drawing -------------------------

	auto draw_player = [&] () -> void {
		al_set_target_bitmap(al_get_backbuffer(window));

		if (dir == LEFT) {
			
			if (attack)
				al_draw_bitmap_region(*attack_sprite, attack_source->get_sx(), attack_source->get_sy(), attack_source->get_sw(), attack_source->get_sh(), x - 32 - 9, y, 0);
	
			else if (actual_character == KLONOA && klonoa_mode == SAMURAI) {

				if (action1 == FALL || action1 == JUMP)
					al_draw_bitmap_region(*sword_sprite, ws_source->get_sx(), ws_source->get_sy(), ws_source->get_sw(), ws_source->get_sh(), x - 9, y, 0);
				
				else if (action2 == MOVE && move_source.get_sx_index() > 1)
					al_draw_bitmap(*sword_sprite, x - 9 - 2, y, 0);

				else
					al_draw_bitmap(*sword_sprite, x - 9, y, 0);
			
			}

		}



		al_draw_bitmap_region(*player_sprite, player_source->get_sx(), player_source->get_sy(), player_source->get_sw(), player_source->get_sh(), x, y, 0);



		if (dir == RIGHT) {
			
			if (attack)
				al_draw_bitmap_region(*attack_sprite, attack_source->get_sx(), attack_source->get_sy(), attack_source->get_sw(), attack_source->get_sh(), x, y, 0);

			else if (actual_character == KLONOA && klonoa_mode == SAMURAI) {

				if (action1 == FALL || action1 == JUMP)
					al_draw_bitmap_region(*sword_sprite, ws_source->get_sx(), ws_source->get_sy(), ws_source->get_sw(), ws_source->get_sh(), x, y, 0);

				else if (action2 == MOVE && move_source.get_sx_index() > 1)
					al_draw_bitmap(*sword_sprite, x - 2, y, 0);

				else	
					al_draw_bitmap(*sword_sprite, x, y, 0);
			
			}
			
		}
	
	};

	auto draw_scenario = [&] () -> void {
		al_draw_line(0, 232, W, 232, COLOR(14, 98, 130), 9.5f);
		al_draw_rectangle(350, 200, 400, 232, COLOR(32, 199, 2), 3.9f);
		al_draw_rectangle(50, 200, 80, 232, COLOR(32, 199, 2), 3.9f);
	};

	// ---------------------------------



	// Game loop -----------------------

	al_start_timer(timer);

	while (!game_over) {

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			al_get_keyboard_state(&key);
			
			update_dir_and_actions();
			update_sources_and_sprites();
			update_pos();

			if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
				game_over = true;

		} else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_over = true;

		al_clear_to_color(COLOR(12, 24, 52));
		draw_scenario();
		draw_player();
		al_flip_display();
	
	}

	// ---------------------------------



	// Game end ------------------------

	al_shutdown_primitives_addon();

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
	al_destroy_bitmap(kwcl);
	al_destroy_bitmap(kwcr);
	al_destroy_bitmap(vil);
	al_destroy_bitmap(vir);
	al_destroy_bitmap(vwl);
	al_destroy_bitmap(vwr);
	al_destroy_bitmap(vjl);
	al_destroy_bitmap(vjr);
	al_destroy_bitmap(vfl);
	al_destroy_bitmap(vfr);
	al_destroy_bitmap(vkl);
	al_destroy_bitmap(vkr);

	al_destroy_bitmap(wbl);
	al_destroy_bitmap(wbr);
	al_destroy_bitmap(wcl);
	al_destroy_bitmap(wcr);
	al_destroy_bitmap(kl);
	al_destroy_bitmap(kr);

	al_destroy_bitmap(wsl);
	al_destroy_bitmap(wsr);
	al_destroy_bitmap(wsfl);
	al_destroy_bitmap(wsfr);
	al_destroy_bitmap(wsjl);
	al_destroy_bitmap(wsjr);

	PRINT("\n--- game over ---\n\n")
	return 0;

	// ---------------------------------

}



// ----------------------------------------------------------------------------------



// Functions definition ----------

const void switch_character() {
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

const void add_to_map(const int x1, const int x2) { x_pos.push_back({x1, x2}); }

const bool check_x_collision() {
	
	for (auto i : x_pos)
		if ( (dir == LEFT && x == i.second) ||
			(dir == RIGHT && x + 32 == i.first) )
			return true;

	return false;
}

// -------------------------------



// Methods definition ------------

const bool source::check_actual_character() const {
	if (actual_character == this->character)
		return true;

	else
		return false;

}

const bool source::check_actual_action(const int action_n) const {
	if (action_n == 0){

		if ( (player_source == this || attack_source == this) && attack && this->get_sx_index() == this->sx_lim && this->get_sy_index() == this->sy_lim)
			attack = false;

	} else if (action_n == 1) {

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

const void source::update_sx(const int action_n) const {
	if ( (this->character == 2 || this->check_actual_character()) && this->check_actual_action(action_n) || (this->is_attack && attack) ) {

		if (this->get_sx_index() < this->sx_lim)
			this->sx += this->sw;

		else if (this->set_to_0)
			this->sx = 0;
	
	} else
		this->sx = -(this->sw);

}

const void source::update_sy(const int action_n) const {
	if ( (this->character == 2 || this->check_actual_character()) && this->check_actual_action(action_n) || (this->is_attack && attack) ) {

		if (this->get_sx_index() < this->sy_lim)
			this->sy += this->sh;

		else if (this->set_to_0)
			this->sy = 0;
	
	} else
		this->sy = -(this->sh);

}

const void source::update_sx(const int action_n1, const int action_n2) const {
	if ( (this->character == 2 || this->check_actual_character()) && this->check_actual_action(action_n1) && this->check_actual_action(action_n2) || (this->is_attack && attack) ) {

		if (this->get_sx_index() < this->sx_lim)
			this->sx += this->sw;

		else if (this->set_to_0)
			this->sx = 0;
	
	} else
		this->sx = -(this->sw);

}

const void source::update_sy(const int action_n1, const int action_n2) const {
	if ( (this->character == 2 || this->check_actual_character()) && this->check_actual_action(action_n1) && this->check_actual_action(action_n2) || (this->is_attack && attack) ) {

		if (this->get_sx_index() < this->sy_lim)
			this->sy += this->sh;

		else if (this->set_to_0)
			this->sy = 0;
	
	} else
		this->sy = -(this->sh);

}



const void ws_source::update_sx(const int action_n) const {
	if ( (this->character == 2 || this->check_actual_character()) && this->check_actual_action(action_n) || (this->is_attack && attack) && klonoa_mode == SAMURAI) {

		if (this->get_sx_index() < this->sx_lim)
			this->sx += this->sw;

		else if (this->set_to_0)
			this->sx = 0;
	
	} else
		this->sx = -(this->sw);

}

const void ws_source::update_sy(const int action_n) const {
	if ( (this->character == 2 || this->check_actual_character()) && this->check_actual_action(action_n) || (this->is_attack && attack) && klonoa_mode == SAMURAI) {

		if (this->get_sx_index() < this->sy_lim)
			this->sy += this->sh;

		else if (this->set_to_0)
			this->sy = 0;
	
	} else
		this->sy = -(this->sh);

}

const void ws_source::update_sx(const int action_n1, const int action_n2) const {
	if ( (this->character == 2 || this->check_actual_character()) && this->check_actual_action(action_n1) && this->check_actual_action(action_n2) || (this->is_attack && attack) && klonoa_mode == SAMURAI) {

		if (this->get_sx_index() < this->sx_lim)
			this->sx += this->sw;

		else if (this->set_to_0)
			this->sx = 0;
	
	} else
		this->sx = -(this->sw);

}

const void ws_source::update_sy(const int action_n1, const int action_n2) const {
	if ( (this->character == 2 || this->check_actual_character()) && this->check_actual_action(action_n1) && this->check_actual_action(action_n2) || (this->is_attack && attack) && klonoa_mode == SAMURAI) {

		if (this->get_sx_index() < this->sy_lim)
			this->sy += this->sh;

		else if (this->set_to_0)
			this->sy = 0;
	
	} else
		this->sy = -(this->sh);

}

// -------------------------------