#include <iostream>
#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <window.hpp>
#include <image.hpp>
#include <character.hpp>



#define PRINTLN(txt) std::cout << txt << std::endl;



std::queue<std::string> msgs;



float get_current_time() { return SDL_GetTicks() / 1000.0f; }

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	window win = window("Klonoa Dimensions", 720, 480);

	character klonoa = character(vec2f(0, 0), vec2f(64, 64), vec2f(0, 0), vec2f(100, 5));
	image k = image(win, "res/sprites/klonoa/character/Klonoa Idle Right.png", { 0, 0, 16, 16 }, { 0, 0, 0, 0 });
    image harold = image(win, "res/textures/hide the pain.jpg", { 0, 0, 1200, 800 }, { 0, 0 });
	area_manager area_man = area_manager();

    area_man.register_collision_area(vec2f(100, 100), vec2f(150, 150), &harold);



    auto draw = [&] () -> void {
		area_man.draw_areas();
        SDL_Rect rec = k.get_des();

        k.change_pos(klonoa.get_xy().x, klonoa.get_xy().y);
        k.change_size(klonoa.get_wh().x, klonoa.get_wh().y);

        k.draw();

        k.change_pos(rec.x, rec.y);
        k.change_size(rec.w, rec.h);
    };



    bool running = true;
    SDL_Event evn;

	float current_time = get_current_time();

    while (running) {

		float new_time = get_current_time();
		float delta_time = new_time - current_time;
		current_time = new_time;

        while (SDL_PollEvent(&evn))
            if (evn.type == SDL_QUIT)
                running = false;

		const Uint8* key = SDL_GetKeyboardState(nullptr);

		klonoa.update_datas(key, area_man);
		klonoa.update_pos(delta_time, 100, area_man);



        while (!msgs.empty()) {

            PRINTLN(msgs.front())
            msgs.pop();

        }



        win.clear();
        draw();
        win.update();

    }

    SDL_Quit();
    IMG_Quit();
    return 0;
}