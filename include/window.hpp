#pragma once



#include <SDL2/SDL.h>
#include <image.hpp>
#include <sprite.hpp>
#include <area.hpp>
#include <character.hpp>



class window {
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	const int w, h, flags;

public:
	window(const char* title, const int w, const int h, const int flags = SDL_WINDOW_SHOWN) :
		win(nullptr), ren(nullptr), w(w), h(h), flags(flags) {
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->w, this->h, this->flags);
		this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED);
	}
	window(const char* title, const window& wnd) :
		win(nullptr), ren(nullptr), w(wnd.get_w()), h(wnd.get_h()), flags(wnd.get_flags()) {
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->w, this->h, this->flags);
		this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED);
	}
	window(const char* title, const window&& wnd) :
		win(nullptr), ren(nullptr), w(wnd.get_w()), h(wnd.get_h()), flags(wnd.get_flags()) {
		this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->w, this->h, this->flags);
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
	int get_flags() const { return this->flags; }

	void clear() const;
	void clear(const int r, const int g, const int b) const;
	void clear(const int r, const int g, const int b, const int a) const;

	void render(const image& img) const;
	void render(const sprite& spr) const;
	void render(const area_manager& area_man) const;
	void render(const character& chr) const;

	void update() const;

};