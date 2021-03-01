#include <iostream>
#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <window.hpp>



#define PRINTLN(txt) std::cout << txt << std::endl;



std::queue<std::string> msgs;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    window win = window("Klonoa Dimensions", 720, 480);

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
        win.update();

    }

    SDL_Quit();
    IMG_Quit();
    return 0;
}