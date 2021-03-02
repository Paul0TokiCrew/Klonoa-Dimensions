#include <iostream>
#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <window.hpp>
#include <image.hpp>
#include <character.hpp>



#define PRINTLN(txt) std::cout << txt << std::endl;
#define GRAVITY 500



std::queue<std::string> msgs;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    window win = window("Klonoa Dimensions", 720, 480);

    character klonoa = character(vec2f(0, 0), vec2f(64, 64), vec2f(0, 0), vec2f(100, GRAVITY));
    image k = image(win, "res/sprites/klonoa/character/Klonoa Idle Right.png", { 0, 0, 16, 16 }, { 0, 0, 0, 0 } );
    area_manager area_man = area_manager();

    area_man.register_area(vec2f(100, 100), vec2f(50, 50));



    auto draw = [&] () -> void {
        SDL_Rect rec = k.get_des();

        k.change_pos(klonoa.get_xy().x, klonoa.get_xy().y);
        k.change_size(klonoa.get_wh().x, klonoa.get_wh().y);

        k.draw();

        k.change_pos(rec.x, rec.y);
        k.change_size(rec.w, rec.h);
    };



    bool running = true;
    SDL_Event evn;

    while (running) {

        while (SDL_PollEvent(&evn))
            if (evn.type == SDL_QUIT)
                running = false;

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