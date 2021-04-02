#include <game.hpp>



extern float get_current_time();

int main(int argc, char* argv[]) {
	if (!game::init()) {
		log_e();
		return 1;

	}

	window win = window("Klonoa Dimensions", 720, 480);

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

	while (game::running) {

		float new_time = get_current_time();
		float delta_time = new_time - current_time;
		current_time = new_time;

		while (SDL_PollEvent(&evn))
			if (evn.type == SDL_QUIT)
				game::running = false;

		const Uint8* key = SDL_GetKeyboardState(nullptr);

		klonoa.update_datas(key, area_man);
		klonoa.update_sprites();
		klonoa.update_pos(delta_time, area_man);
		klonoa_cam.update_cam(klonoa.get_xy());
		area_man.change_areas_pos(klonoa_cam.get_cam_pos());

		//log_m();

		win.clear();
		draw();
		win.update();

	}

	SDL_Quit();
	IMG_Quit();
	return 0;
}
