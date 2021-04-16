#include <game.hpp>



float get_current_time() { return SDL_GetTicks() / 1000.0f; }

void game::play() {
	if (this->init())
		log_e();



	crd.init();

	crd.register_comp<c_position>();
	crd.register_comp<c_movement>();

	auto phy = crd.register_sys<physics>();

	signature phy_sign;
	phy_sign.set(crd.get_comp_type<c_position>());
	phy_sign.set(crd.get_comp_type<c_movement>());

	crd.set_sys_signature<physics>(phy_sign);

	entity klonoa_ent = crd.create_ent();
	c_position klonoa_pos { vec2f(0), vec2f(64) };
	c_movement klonoa_mov { vec2f(0, 1), vec2f(0), vec2f(0, 0), vec2f(140, GRAVITY) };

	crd.add_comp(klonoa_ent, klonoa_pos);
	crd.add_comp(klonoa_ent, klonoa_mov);

	window win = window(this->title, 720, 480);

	sprite r_sprites[] = {
		sprite(win.get_ren(), "res/sprites/klonoa/character/Klonoa Idle Right.png", { 0, 0, 16, 16 }, { 0, 0, 64, 64 }, 0, 21, 16, 0, 10),
		sprite(win.get_ren(), "res/sprites/klonoa/character/Klonoa Walk Right.png", { 0, 0, 16, 16 }, { 0, 0, 64, 64 }, 0, 3, 16, 0, 10)
	};

	sprite l_sprites[] = {
		sprite(win.get_ren(), "res/sprites/klonoa/character/Klonoa Idle Left.png", { 0, 0, 16, 16 }, { 0, 0, 64, 64 }, 0, 21, 16, 0, 10),
		sprite(win.get_ren(), "res/sprites/klonoa/character/Klonoa Walk Left.png", { 0, 0, 16, 16 }, { 0, 0, 64, 64 }, 0, 3, 16, 0, 10)
	};

	character klonoa = character(vec2f(0), vec2f(64), vec2f(0, 1), vec2f(0), vec2f(140, GRAVITY), r_sprites, l_sprites);
	camera klonoa_cam = camera(klonoa.get_xy());

	image harold = image(win.get_ren(), "res/textures/hide the pain.jpg", { 0, 0, 1200, 800 }, { 0, 400, 720, 80 });
	image putin = image(win.get_ren(), "res/textures/putin.jpg", { 0, 0, 1200, 1200 }, { 500, 280, 100, 100 });

	area_manager area_man = area_manager();

	area_man.register_collision_area(vec2f(0, 400), vec2f(720, 480), &harold, "Down");
	area_man.register_collision_area(vec2f(500, 280), vec2f(600, 380), &putin);

	area_man.register_fric_area(vec2f(0, 0), vec2f(720, 480), FRIC);

	auto draw = [&] () -> void {
		win.render(area_man);
		if (klonoa.get_current_sprite() != nullptr)
			win.render(klonoa);

	};



	SDL_Event evn;

	float current_time = get_current_time();

	while (this->running) {

		float new_time = get_current_time();
		float delta_time = new_time - current_time;
		current_time = new_time;

		while (SDL_PollEvent(&evn))
			if (evn.type == SDL_QUIT)
				this->running = false;

		const Uint8* key = SDL_GetKeyboardState(nullptr);

		klonoa.update_datas(key, area_man);
		klonoa.update_sprites();
		klonoa.update_pos(delta_time, area_man);
		//phy->update(delta_time, area_man);

		klonoa_cam.update_cam(klonoa.get_xy());
		area_man.change_areas_pos(klonoa_cam.get_cam_pos());

		//log_m();

		win.clear();
		draw();
		win.update();

	}

	SDL_Quit();
	IMG_Quit();
}

bool game::init() {
	static bool called = false;

	if (called) {
		warnings.push("WARNING: calling \"game::init()\" multiple times");
		return false;

	}

	called = true;
	bool initialized = true;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		errors.push("ERROR: could not initialize SDL library");
		initialized = false;

	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
		errors.push("ERROR: could not initialize SDL_image library");
		initialized = false;

	}

	if (initialized)
	    game::running = true;

	return initialized;
}