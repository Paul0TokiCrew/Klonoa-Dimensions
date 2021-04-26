#include <area.hpp>



void area_manager::render(SDL_Renderer* ren) const {
	SDL_Rect src, des;

	for (const auto i : this->fric_areas) {

		const image* img = i.img;
		if (!img)
			continue;

		src = img->get_src();
		des = img->get_des();

		SDL_RenderCopy(ren, img->get_img(), &src, &des);

	}

	for (const auto i : this->coll_areas) {

		const image* img = i.img;
		if (!img)
			continue;

		src = img->get_src(),
		des = img->get_des();

		SDL_RenderCopy(ren, img->get_img(), &src, &des);

	}

}

void area_manager::register_collision_area(const collision_area ca) {
	if (ca.xy1 == ca.xy2)
		return;

	this->coll_areas.push_back(ca);
}


void area_manager::register_friction_area(const friction_area fa) {
	if (std::ceil(fa.friction) < 0)
		return;

	this->fric_areas.push_back(fa);
}

bool area_manager::check_trigger(const area a) const {

	for (const auto i : this->coll_areas) {

		if (
			a.xy1.x <= i.xy2.x &&
			a.xy2.x >= i.xy1.x &&
			a.xy1.y <= i.xy2.y &&
			a.xy2.y >= i.xy1.y
		)
			return true;

	}

	return false;
}

bool area_manager::check_up_collision(const area a, vec2f* const diff) const {

	for (const auto i : this->coll_areas) {

		if (
			std::strchr(i.collision, 'U') != nullptr &&
			(
				(
					a.xy1.x < i.xy2.x &&
					a.xy1.x > i.xy1.x
				) ||
				(
					a.xy2.x > i.xy1.x &&
					a.xy2.x < i.xy2.x
				)
			) &&
			a.xy1.y <= i.xy2.y &&
			a.xy2.y > i.xy2.y &&
			a.xy1.y > i.xy1.y
		) {
			diff->y = i.xy2.y - a.xy1.y;
			return true;

		}

	}

	return false;
}

bool area_manager::check_down_collision(const area a, vec2f* const diff) const {

	for (const auto i : this->coll_areas) {

		if (
			std::strchr(i.collision, 'D') != nullptr &&
			(
				(
					a.xy1.x < i.xy2.x &&
					a.xy1.x > i.xy1.x
				) ||
				(
					a.xy2.x > i.xy1.x &&
					a.xy2.x < i.xy2.x
				)
			) &&
			a.xy1.y < i.xy1.y &&
			a.xy2.y >= i.xy1.y &&
			a.xy2.y < i.xy2.y
		) {
			diff->y = i.xy1.y - a.xy2.y;
			return true;

		}

	}

	return false;
}

bool area_manager::check_right_collision(const area a, vec2f* const diff) const {

	for (const auto i : this->coll_areas) {

		if (
			std::strchr(i.collision, 'R') != nullptr &&
			a.xy1.x < i.xy2.x &&
			a.xy2.x >= i.xy1.x &&
			(
				(
					a.xy1.y < i.xy2.y &&
					a.xy1.y > i.xy1.y
				) ||
				(
					a.xy2.y > i.xy1.y &&
					a.xy2.y < i.xy2.y
				)
			) &&
			a.xy2.x < i.xy2.x
		) {
			diff->x = i.xy1.x - a.xy2.x;
			return true;

		}

	}

	return false;
}

bool area_manager::check_left_collision(const area a, vec2f* const diff) const {

	for (auto i : this->coll_areas) {

		if (
			std::strchr(i.collision, 'L') != nullptr &&
			a.xy1.x <= i.xy2.x &&
			a.xy2.x > i.xy2.x &&
			(
				(
					a.xy1.y < i.xy2.y &&
					a.xy1.y > i.xy1.y
				) ||
				(
					a.xy2.y > i.xy1.y &&
					a.xy2.y < i.xy2.y
				)
			) &&
			a.xy1.x > i.xy1.x
		) {
			diff->x = i.xy1.x - a.xy1.x;
			return true;

		}

	}

	return false;
}

float area_manager::get_friction(const area a) const {
	std::priority_queue<float, std::vector<float>, std::greater<float>> fric;

	for (const auto i : this->fric_areas) {

		if (
			a.xy1.x <= i.xy2.x &&
			a.xy2.x >= i.xy1.x &&
			a.xy1.y <= i.xy2.y &&
			a.xy2.y >= i.xy1.y
		)
			fric.push(i.friction);

	}

	if (!(fric.empty()))
		return fric.top();

	return 0;

}

void area_manager::change_areas_pos(const vec2f mod) {

	for (const auto i : this->fric_areas) {

		image* img = i.img;
		if (!img)
			continue;

		const vec2f xy = i.xy1;

		img->change_pos(xy.x - std::ceil(mod.x), xy.y - std::ceil(mod.y));

	}

	for (const auto i : this->coll_areas) {

		image* img = i.img;
		if (!img)
			continue;

		const vec2f xy = i.xy1;

		img->change_pos(xy.x - std::ceil(mod.x), xy.y - std::ceil(mod.y));

	}

}