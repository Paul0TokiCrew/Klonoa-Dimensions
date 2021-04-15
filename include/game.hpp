#pragma once



#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <log.hpp>
#include <ECS.hpp>
#include <physics.hpp>
#include <image.hpp>
#include <area.hpp>
#include <character.hpp>
#include <camera.hpp>
#include <window.hpp>



class game {
private:
	const char* title;
	bool running;

	bool init();

public:
	game(const char* title) :
		title(title) { }
	~game() { }

	void play();

};