#include <area.hpp>



void area_manager::register_collision_area(const vec2f xy1, const vec2f xy2, image* const tex, const char* coll) {
	if (xy1 == xy2)
		return;

	this->collision_areas.push_back(std::make_tuple(xy1, xy2, coll));

	if (tex != nullptr)
		this->img_areas.push_back(std::make_pair(tex, xy1));

}


void area_manager::register_fric_area(const vec2f xy1, const vec2f xy2, const float fric, image* const tex) {
	if (std::ceil(fric) < 0)
		return;

	this->fric_areas.push_back(std::make_tuple(xy1, xy2, fric));

	if (tex != nullptr)
		this->img_areas.push_back(std::make_pair(tex, xy1));

}

bool area_manager::check_trigger(const vec2f other_xy1, const vec2f other_xy2) const {

	for (auto i : this->collision_areas) {

		if (
			other_xy1.x <= std::get<1>(i).x &&
			other_xy2.x >= std::get<0>(i).x &&
			other_xy1.y <= std::get<1>(i).y &&
			other_xy2.y >= std::get<0>(i).y
		)
			return true;

	}

	return false;
}

bool area_manager::check_up_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff) const {

	for (auto i : this->collision_areas) {

		if (
			std::strchr(std::get<2>(i), 'U') != nullptr &&
			other_xy1.x < std::get<1>(i).x &&
			other_xy2.x > std::get<0>(i).x &&
			other_xy1.y <= std::get<1>(i).y &&
			other_xy2.y > std::get<1>(i).y &&
			other_xy1.y > std::get<0>(i).y
		) {
			diff->y = std::get<1>(i).y - other_xy1.y;
			return true;

		}

	}

	return false;
}

bool area_manager::check_down_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff) const {

	for (auto i : this->collision_areas) {

		if (
			std::strchr(std::get<2>(i), 'D') != nullptr &&
			other_xy1.x < std::get<1>(i).x &&
			other_xy2.x > std::get<0>(i).x &&
			other_xy1.y < std::get<0>(i).y &&
			other_xy2.y >= std::get<0>(i).y &&
			other_xy2.y < std::get<1>(i).y 
		) {
			diff->y = std::get<0>(i).y - other_xy2.y;
			return true;

		}

	}

	return false;
}

bool area_manager::check_right_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff) const {

	for (auto i : this->collision_areas) {

		if (
			std::strchr(std::get<2>(i), 'R') != nullptr &&
			other_xy1.x < std::get<0>(i).x &&
			other_xy2.x >= std::get<0>(i).x &&
			other_xy1.y < std::get<1>(i).y &&
			other_xy2.y > std::get<0>(i).y &&
			other_xy2.x < std::get<1>(i).x
		) {
			diff->x = std::get<0>(i).x - other_xy2.x;
			return true;

		}

	}

	return false;
}

bool area_manager::check_left_collision(const vec2f other_xy1, const vec2f other_xy2, vec2f* const diff) const {

	for (auto i : this->collision_areas) {

		if (
			std::strchr(std::get<2>(i), 'L') != nullptr &&
			other_xy1.x <= std::get<1>(i).x &&
			other_xy2.x > std::get<1>(i).x &&
			other_xy1.y < std::get<1>(i).y &&
			other_xy2.y > std::get<0>(i).y &&
			other_xy1.x > std::get<0>(i).x
		) {
			diff->x =std::get<1>(i).x - other_xy1.x;
			return true;

		}

	}

	return false;
}

float area_manager::get_fric(const vec2f other_xy1, const vec2f other_xy2) const {
	std::priority_queue<float, std::vector<float>, std::greater<float>> fric;

	for (auto i : this->fric_areas) {

		if (
			other_xy1.x <= std::get<1>(i).x &&
			other_xy2.x >= std::get<0>(i).x &&
			other_xy1.y <= std::get<1>(i).y &&
			other_xy2.y >= std::get<0>(i).y
		)
			fric.push(std::get<2>(i));

	}

	if (!(fric.empty()))
		return fric.top();

	return 0;

}

void area_manager::change_areas_pos(const vec2f mod) {

	for (auto i : this->img_areas) {

		image& img = *(i.first);
		const vec2f& xy = i.second;
		img.change_pos(xy.x - std::ceil(mod.x), xy.y - std::ceil(mod.y));

	}

}