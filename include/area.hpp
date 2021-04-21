#pragma once



#include <cstring>
#include <vector>
#include <queue>
#include <tuple>
#include <vec2f.hpp>
#include <image.hpp>



class area {
public:
	area(const vec2f xy1 = vec2f(0, 0), const vec2f xy2 = vec2f(0, 0)) :
		xy1(xy1), xy2(xy2) { }
	~area() { }

	vec2f xy1, xy2;

};

class collision_area : public area {
public:
	collision_area(const vec2f xy1 = vec2f(0, 0), const vec2f xy2 = vec2f(0, 0), char* collision = "UDRL") :
		area(xy1, xy2), collision(collision) { }
	~collision_area() { }

	char* collision;

};

class friction_area : public area {
public:
	friction_area(const vec2f xy1 = vec2f(0, 0), const vec2f xy2 = vec2f(0, 0), const float friction = 0.0f) :
		area(xy1, xy2), friction(friction) { }
	~friction_area() { }

	float friction;

};



class area_manager {
private:
	std::vector<std::pair<image* const, const vec2f>> img_areas; 
	std::vector<collision_area> coll_areas;
	std::vector<friction_area> fric_areas;

public:
	area_manager() { }
	~area_manager() { }

	using img_area = std::pair<image* const, const vec2f>;

	unsigned get_img_areas_size() const { return this->img_areas.size(); }
	img_area get_img_area(const unsigned index = 0) const { return index <= this->img_areas.size() ?
		this->img_areas[index] : std::make_pair(nullptr, vec2f(0, 0)); }

	void register_collision_area(const collision_area ca, image* const tex = nullptr);
	void register_friction_area(const friction_area fa, image* const tex = nullptr);

	bool check_trigger(const area a) const;

	bool check_up_collision(const area a, vec2f* const diff = nullptr) const;
	bool check_down_collision(const area a, vec2f* const diff = nullptr) const;
	bool check_right_collision(const area a, vec2f* const diff = nullptr) const;
	bool check_left_collision(const area a, vec2f* const diff = nullptr) const;

	float get_friction(const area a) const;

	void change_areas_pos(const vec2f mod);

};