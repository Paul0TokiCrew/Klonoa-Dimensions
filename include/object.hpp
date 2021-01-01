#pragma once



#include <vector>
#include <image.hpp>



class object {
public:
	object() { }
	~object() { }

	static std::vector<std::pair<
		std::pair<int, int>,
		std::pair<int, int>
	>> pos;
	static std::vector<image*> textures;
	static std::vector<const char*> ids;

	static void add_obj(SDL_Rect rec, const char* id);
	static void add_obj(SDL_Rect rec, image& img, const char* id);

	static void del_obj(const int index);

};