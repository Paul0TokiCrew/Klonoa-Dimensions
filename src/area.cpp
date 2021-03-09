#include <area.hpp>



void area_manager::register_collision_area(const vec2f xy1, const vec2f xy2, image* tex) {
	this->collision_areas.push_back(std::make_tuple(xy1, xy2, tex));
}

bool area_manager::check_trigger(const vec2f other_xy1, const vec2f other_xy2) const {

	for (auto i : this->collision_areas) {

		if (
			other_xy1.x <= std::get<0>(i).x &&
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

void area_manager::change_areas_pos(const vec2f mod) {

	for (auto i : this->collision_areas) {

		image*& img = std::get<2>(i);
		img->change_pos(img->get_old_des().x - std::ceil(mod.x), img->get_old_des().y - std::ceil(mod.y));

	}

}

void area_manager::draw_areas() const {

	for (auto i : this->collision_areas) {

		image*& img = std::get<2>(i);

		if (img != nullptr)
			img->draw();


	}

}