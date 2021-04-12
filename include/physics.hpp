#include <ECS.hpp>

struct c_position { vec2f xy, wh; };

struct c_movement { vec2f dir, vel, goal_vel; };

class physics : public system {
public:
	physics() { }
	~physics() { }

};