#pragma once



#include <log.hpp>
#include <ECS.hpp>
#include <vec2f.hpp>
#include <area.hpp>



struct c_position { vec2f xy, wh; };

struct c_movement { vec2f dir, vel, goal_vel; };



class physics : public system {
public:
	physics() { }
	~physics() { }

	void update(const float delta_time, const area_manager& area_man);

};