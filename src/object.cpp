#include <vector>
#include <image.hpp>
#include <object.hpp>



std::vector<std::pair<
	std::pair<int, int>,
	std::pair<int, int>
>> object::pos;
std::vector<image*> object::textures;
std::vector<const char*> object::ids;

void object::add_obj(SDL_Rect rec, const char* id) {
	object::pos.push_back( {
		{ rec.x, rec.y },
		{ rec.x + rec.w, rec.y + rec.h }
	} );

	object::textures.push_back(nullptr);
	object::ids.push_back(id);
}

void object::add_obj(SDL_Rect rec, image& img, const char* id) {
	object::pos.push_back( {
		{ rec.x, rec.y },
		{ rec.x + rec.w, rec.y + rec.h }
	} );

	object::textures.push_back(&img);
	object::ids.push_back(id);
}

void object::del_obj(const int index) {
	object::pos.erase(object::pos.begin() + index);
	object::textures.erase(object::textures.begin() + index);
	object::ids.erase(object::ids.begin() + index);
}