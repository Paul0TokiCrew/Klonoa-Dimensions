#pragma once



#include <vec2f.hpp>



class camera {
private:
	vec2f cam_pos, ref;
	const vec2f lim;

public:
	camera(const vec2f ref, const vec2f lim = vec2f(0, 0)) :
		cam_pos(0, 0), ref(ref), lim(lim) { }
	~camera() { }

	vec2f get_cam_pos() const { return this->cam_pos; }
	vec2f get_lim() const { return this->lim; }

	void update_cam(const vec2f new_ref);

};