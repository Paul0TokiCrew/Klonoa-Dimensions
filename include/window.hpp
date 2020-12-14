#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class window {
private:
	SDL_Window* win;
	SDL_Renderer* ren;

public:
	window() : win(nullptr), ren(nullptr) { }
	window(const char* title, int w, int h) : win(nullptr), ren(nullptr) {
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_POS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED);
	}
	~window() {
		SDL_DestroyWindow(this->win);
		SDL_DestroyRenderer(this->ren);
		delete this;
	}

	SDL_Window* get_win() const { return this->win; }
	SDL_Renderer* get_ren() const { return this->ren; }

	void clear() const;
	void clear(int r, int g, int b, int a) const;
	void update() const;

};