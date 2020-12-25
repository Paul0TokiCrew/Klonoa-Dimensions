#pragma once



#include <string>
#include <vector>



class character {
private:
	const int speed, jump_height;
	const bool jump_many_times;

public:
	character(const int speed, const int jump_height, const bool jump_many_times) :
	speed(speed), jump_height(jump_height), jump_many_times(jump_many_times) { }
	~character() { }

	int get_speed() const { return this->speed; }
	int get_jump_height() const { return this->jump_height; }
	bool get_jump_many_times() const { return this->jump_many_times; }

};