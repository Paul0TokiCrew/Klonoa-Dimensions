#pragma once



#include <cstring>
#include <vector>
#include <queue>
#include <tuple>
#include <utility>
#include <vec2f.hpp>
#include <image.hpp>



class area_manager {
private:
	image* bg;
	std::vector<std::pair<image* const, const vec2f>> img_areas; 
	std::vector<std::tuple<vec2f, vec2f, const char*>> collision_areas;
	std::vector<std::tuple<vec2f, vec2f, const float>> fric_areas;

public:
	area_manager() :
		bg(nullptr) { }
	area_manager(image* bg) :
		bg(bg) { }
	~area_manager() { }

	void change_bg(image* bg) { this->bg = bg; }

	void register_collision_area(const vec2f xy1, const vec2f xy2, image* const tex = nullptr, const char* coll = "UDRL");
	void register_fric_area(const vec2f xy1, const vec2f xy2, const float fric = 1, image* const tex = nullptr);

	bool check_trigger(const vec2f other_xy1, const vec2f other_xy2) const;

	bool check_up_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff = nullptr) const;
	bool check_down_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff = nullptr) const;
	bool check_right_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff = nullptr) const;
	bool check_left_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff = nullptr) const;

	float get_fric(const vec2f other_xy1, const vec2f other_xy2) const;

	void change_areas_pos(const vec2f mod);
	void draw_areas() const;

};