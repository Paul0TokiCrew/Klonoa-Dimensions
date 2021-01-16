#pragma once



#include <player_data.hpp>
#include <object.hpp>



#define RIGHT 0
#define LEFT 1

#define IDLE 2
#define MOVE 3

#define STAND 4
#define FALL 5
#define JUMP 6

#define CHARACTER_REC { character::x, character::y, character::w, character::h }



class character {
private:
	const int speed, jump_height;
	const bool jump_many_times;

public:
	character(const int speed, const int jump_height, const bool jump_many_times) :
	speed(speed), jump_height(jump_height), jump_many_times(jump_many_times) { }
	~character() { }

	static int x, y, w, h;
	static player_data dir, action1, action2;

	int get_jump_height() { return this->jump_height; }
	bool get_jump_many_times() { return this->jump_many_times; }

	friend void move_right(character* obj);
	friend void move_left(character* obj);

};