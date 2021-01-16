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

bool object::check_up_collision(SDL_Rect rec) {
	auto i = object::pos.begin();
	auto j = object::ids.begin();

	for (; i != object::pos.end() && j != object::ids.end(); ++i, ++j)
		if (strchr(*j, 'u') != nullptr &&
			rec.y == i->second.second &&
			(rec.x < i->second.first && rec.x + rec.w > i->first.first) )
			return true;

	return false;
}

bool object::check_down_collision(SDL_Rect rec) {
	auto i = object::pos.begin();
	auto j = object::ids.begin();

	for (; i != object::pos.end() && j != object::ids.end(); ++i, ++j)
		if (strchr(*j, 'd') != nullptr &&
			rec.y + rec.h == i->first.second &&
			(rec.x < i->second.first && rec.x + rec.w > i->first.first) )
			return true;

	return false;
}

bool object::check_right_collision(SDL_Rect rec) {
	auto i = object::pos.begin();
	auto j = object::ids.begin();

	for (; i != object::pos.end() && j != object::ids.end(); ++i, ++j)
		if (strchr(*j, 'r') != nullptr &&
			rec.x + rec.w == i->first.first &&
			(rec.y < i->second.second && rec.y + rec.w > i->first.second) )
			return true;

	return false;
}

bool object::check_left_collision(SDL_Rect rec) {
	auto i = object::pos.begin();
	auto j = object::ids.begin();

	for (; i != object::pos.end() && j != object::ids.end(); ++i, ++j)
		if (strchr(*j, 'l') != nullptr &&
			rec.x == i->second.first &&
			(rec.y < i->second.second && rec.y + rec.w > i->first.second) )
			return true;

	return false;
}