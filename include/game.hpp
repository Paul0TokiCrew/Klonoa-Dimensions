#pragma once



#include <iostream>
#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <window.hpp>
#include <image.hpp>
#include <area.hpp>
#include <character.hpp>
#include <camera.hpp>



#define PRINTLN(txt) std::cout << txt << std::endl;
#define GRAVITY 10000
#define FRIC 400



class game {
private:
	const window win;

public:
	game(const char* title = "Window", const int w = 720, const int h = 480, const int flags = SDL_WINDOW_SHOWN) :
		win(window(title, w, h, flags)) { }
	game(const char* title, const window& wnd) :
		win(title, wnd) { }
	game(const char* title, const window&& wnd) :
		win(title, wnd) { }
	~game() { }

	static bool running;

	static bool init();

};