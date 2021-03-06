#include <game.hpp>



void game::play() {
	if (this->init())
		log_e();



	crd.init();

		crd.register_comp<c_image>();
	crd.register_comp<c_position>();
	crd.register_comp<c_movement>();
	crd.register_comp<c_player_keys>();


	auto rnd = crd.register_sys<renderer>();
	auto phy = crd.register_sys<physics>();
	auto ply = crd.register_sys<player>();

	signature sign;
	sign.set(crd.get_comp_type<c_image>());
	crd.set_sys_signature<renderer>(sign);

	sign.reset();
	sign.set(crd.get_comp_type<c_position>());
	sign.set(crd.get_comp_type<c_movement>());
	crd.set_sys_signature<physics>(sign);

	sign.set(crd.get_comp_type<c_player_keys>());
	crd.set_sys_signature<player>(sign);



	const entity klonoa_ent = crd.create_ent();
	const c_position klonoa_pos { vec2f(W / 2 - 32, H / 2 - 32), vec2f(64) };
	const c_movement klonoa_mov { vec2f(0, 1), vec2f(0), vec2f(0, 0), vec2f(140, GRAVITY) };
	const c_player_keys klonoa_keys { { SDL_SCANCODE_SPACE, SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT } };

	crd.add_comp(klonoa_ent, klonoa_pos);
	crd.add_comp(klonoa_ent, klonoa_mov);
	crd.add_comp(klonoa_ent, klonoa_keys);

	auto& position = crd.get_comp<c_position>(klonoa_ent);
	auto& movement = crd.get_comp<c_movement>(klonoa_ent);



	const window win = window(this->title, W, H);

	sprite r_sprites[] = {
		sprite(win.get_ren(), "res/sprites/klonoa/character/Klonoa Idle Right.png",
			this->make_rect(vec2f(0), vec2f(16)), this->make_rect(position.xy, position.wh), 0, 21, 16, 0, 10),
		sprite(win.get_ren(), "res/sprites/klonoa/character/Klonoa Walk Right.png",
			this->make_rect(vec2f(0), vec2f(16)), this->make_rect(position.xy, position.wh), 0, 3, 16, 0, 10)
	};

	sprite l_sprites[] = {
		sprite(win.get_ren(), "res/sprites/klonoa/character/Klonoa Idle Left.png",
			this->make_rect(vec2f(0), vec2f(16)), this->make_rect(position.xy, position.wh), 0, 21, 16, 0, 10),
		sprite(win.get_ren(), "res/sprites/klonoa/character/Klonoa Walk Left.png",
			this->make_rect(vec2f(0), vec2f(16)), this->make_rect(position.xy, position.wh), 0, 3, 16, 0, 10)
	};

	character klonoa = character(r_sprites, l_sprites);
	camera klonoa_cam = camera(position.xy);

	image harold = image(win.get_ren(), "res/textures/hide the pain.jpg", { 0, 0, 1200, 800 }, { 0, 400, 720, 80 });
	image putin = image(win.get_ren(), "res/textures/putin.jpg", { 0, 0, 1200, 1200 }, { 500, 280, 100, 100 });

	area_manager area_man = area_manager();

	area_man.register_collision_area(collision_area(vec2f(0, 400), vec2f(720, 480), &harold, "Down"));
	area_man.register_collision_area(collision_area(vec2f(500, 280), vec2f(600, 380), &putin, "Down Rigth Left"));

	area_man.register_friction_area(friction_area(vec2f(0, 0), vec2f(720, 480), nullptr, FRIC));

	auto draw = [&] () -> void {
		win.render(area_man);
		if (klonoa.get_current_sprite() != nullptr)
			win.render(klonoa);

	};



	SDL_Event evn;

	float current_time = this->get_current_time();

	while (this->running) {

		const float new_time = this->get_current_time();
		const float delta_time = new_time - current_time;
		current_time = new_time;

		while (SDL_PollEvent(&evn))
			if (evn.type == SDL_QUIT)
				this->running = false;

		const Uint8* key = SDL_GetKeyboardState(nullptr);

		ply->update(key, area_man);
		phy->update(delta_time, area_man);

		klonoa.update_sprites(movement);

		klonoa_cam.update_cam(position.xy);
		area_man.change_areas_pos(klonoa_cam.get_cam_pos());

		log_m();

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

void game::register_components() const {
	crd.register_comp<c_image>();
	crd.register_comp<c_position>();
	crd.register_comp<c_movement>();
	crd.register_comp<c_player_keys>();
}

SDL_Rect game::make_rect(const vec2f xy, const vec2f wh) const {
	SDL_Rect rec;

	rec.x = std::ceil(xy.x);
	rec.y = std::ceil(xy.y);
	rec.w = std::ceil(wh.x);
	rec.h = std::ceil(wh.y);

	return rec;
}
