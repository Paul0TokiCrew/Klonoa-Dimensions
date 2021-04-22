#pragma once



#include <cstring>
#include <vector>
#include <queue>
#include <tuple>
#include <vec2f.hpp>
#include <image.hpp>



class area {
public:
	area(const vec2f xy1 = vec2f(0, 0), const vec2f xy2 = vec2f(0, 0), image* img = nullptr) :
		xy1(xy1), xy2(xy2), img(img) { }
	~area() { }

	vec2f xy1, xy2;
	image* img;

};

class collision_area : public area {
public:
	collision_area(const vec2f xy1 = vec2f(0, 0), const vec2f xy2 = vec2f(0, 0), image* img = nullptr,
		const char* collision = "UDRL") :
		area(xy1, xy2, img), collision(collision) { }
	~collision_area() { }

	const char* collision;

};

class friction_area : public area {
public:
	friction_area(const vec2f xy1 = vec2f(0, 0), const vec2f xy2 = vec2f(0, 0), image* img = nullptr,
		const float friction = 0.0f) :
		area(xy1, xy2, img), friction(friction) { }
	~friction_area() { }

	float friction;

};



class area_manager {
private:
	std::vector<collision_area> coll_areas;
	std::vector<friction_area> fric_areas;

public:
	area_manager() { }
	~area_manager() { }

	void render(SDL_Renderer* ren) const;

	void register_collision_area(const collision_area ca);
	void register_friction_area(const friction_area fa);

	bool check_trigger(const area a) const;

	bool check_up_collision(const area a, vec2f* const diff = nullptr) const;
	bool check_down_collision(const area a, vec2f* const diff = nullptr) const;
	bool check_right_collision(const area a, vec2f* const diff = nullptr) const;
	bool check_left_collision(const area a, vec2f* const diff = nullptr) const;

	float get_friction(const area a) const;

	void change_areas_pos(const vec2f mod);

};