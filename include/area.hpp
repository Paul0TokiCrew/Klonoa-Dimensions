#pragma once



#include <vector>
#include <queue>
#include <tuple>
#include <utility>
#include <vec2f.hpp>
#include <image.hpp>



class area_manager {
private:
	std::vector<std::pair<image*, vec2f>> img_areas; 
	std::vector<std::tuple<vec2f, vec2f>> collision_areas;
	std::vector<std::tuple<vec2f, vec2f, float>> fric_areas;

public:
	area_manager() { }
	~area_manager() { }

	void register_collision_area(const vec2f xy1, const vec2f xy2, image* tex = nullptr);
	void register_fric_area(const vec2f xy1, const vec2f xy2, const float fric = 0, image* tex = nullptr);

	bool check_trigger(const vec2f other_xy1, const vec2f other_xy2) const;

	bool check_up_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff = nullptr) const;
	bool check_down_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff = nullptr) const;
	bool check_right_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff = nullptr) const;
	bool check_left_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff = nullptr) const;

	float get_fric(const vec2f other_xy1, const vec2f other_xy2) const;

	void change_areas_pos(const vec2f mod);
	void draw_areas() const;

};