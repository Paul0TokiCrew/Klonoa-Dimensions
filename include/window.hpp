#pragma once



#include <SDL2/SDL.h>



class window {
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	const int w, h;

public:
	window(const char* title, const int w, const int h) :
	win(nullptr), ren(nullptr), w(w), h(h) {
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
		this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED);

	}
	window(const char* title, const int w, const int h, const int flags) :
	win(nullptr), ren(nullptr), w(w), h(h) {
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
		this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED);

	}
	~window() {
		SDL_DestroyWindow(this->win);
		SDL_DestroyRenderer(this->ren);
	}

	SDL_Window* get_win() const { return this->win; }
	SDL_Renderer* get_ren() const { return this->ren; }
	int get_w() const { return this->w; }
	int get_h() const { return this->h; }

	void clear() const;
	void clear(const int r, const int g, const int b) const;
	void clear(const int r, const int g, const int b, const int a) const;
	void update() const;

};