#pragma once



#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



class image {
protected:
	SDL_Texture* img;
	SDL_Rect src, des;
	const SDL_Rect old_des;
	const char* path;

public:
	image(SDL_Renderer* ren, const char* path, const SDL_Rect src, const SDL_Rect des) :
		img(nullptr), src(src), des(des), old_des(des), path(path) {
		this->img = IMG_LoadTexture(ren, this->path);
	}
	image(SDL_Renderer* ren, const image& tex) :
		img(nullptr), src(tex.get_src()), des(tex.get_des()), old_des(tex.get_old_des()), path(tex.get_path()) {
		this->img = IMG_LoadTexture(ren, this->path);
	}
	image(SDL_Renderer* ren, const image&& tex) :
		img(nullptr), src(tex.get_src()), des(tex.get_des()), old_des(tex.get_old_des()), path(tex.get_path()) {
		this->img = IMG_LoadTexture(ren, this->path);
	}
	virtual ~image() {
		SDL_DestroyTexture(this->img);
	}

	SDL_Texture* get_img() const { return this->img; }
	SDL_Rect get_src() const { return this->src; }
	SDL_Rect get_des() const { return this->des; }
	SDL_Rect get_old_des() const { return this->old_des; }
	const char* get_path() const { return this->path; }

	void change_frame_pos(const int x, const int y);
	void change_frame_size(const int w, const int h);
	void change_pos(const int x, const int y);
	void change_size(const int w, const int h);

	void draw() const { }

};