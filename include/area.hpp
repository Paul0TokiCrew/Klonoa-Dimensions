#pragma once



#include <vector>
#include <tuple>
#include <vec2f.hpp>
#include <image.hpp>



class area_manager {
private:
	std::vector<std::tuple<vec2f, vec2f, image*>> areas;

public:
	area_manager() { }
	~area_manager() { }

	void register_area(const vec2f xy1, const vec2f xy2, image* tex = nullptr);

	bool check_trigger(const vec2f other_xy1, const vec2f other_xy2) const;

	bool check_up_collision(const vec2f other_xy1, const vec2f other_xy2) const;
	bool check_down_collision(const vec2f other_xy1, const vec2f other_xy2) const;
	bool check_right_collision(const vec2f other_xy1, const vec2f other_xy2) const;
	bool check_left_collision(const vec2f other_xy1, const vec2f other_xy2) const;

	void change_areas_pos(const vec2f mod);
	void draw_areas() const;

};