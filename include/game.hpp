#pragma once



#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <log.hpp>
#include <ECS.hpp>
#include <image.hpp>
#include <area.hpp>
#include <character.hpp>
#include <camera.hpp>
#include <window.hpp>



class game {
private:
	const char* title;

public:
	game(const char* title)
		title(title) { }
	~game() { }

	void play();

	static bool running;

	static bool init();

};