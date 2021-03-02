#pragma once



#include <vec2f.hpp>
#include <window.hpp>



class camera {
private:
	vec2f cam_pos, ref;

public:
	camera(const vec2f ref) :
		cam_pos(0, 0), ref(ref) { }
	~camera() { }

	vec2f get_cam_pos() const { return this->cam_pos; }

	void update_cam(const vec2f new_ref);

};