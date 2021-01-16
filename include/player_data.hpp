#pragma once



#include <cstddef>



class player_data {
private:
	int current_data;
	const int min, max;

public:
	player_data(const int min, const int max) :
	current_data(min), min(min), max(max) { }
	player_data(const int data, const int min, const int max) :
	current_data(data), min(min), max(max) { }
	~player_data() { }

	int get_current_data() const { return this->current_data; }

	player_data& operator=(const int new_data);
	friend bool operator==(const player_data& lhs, const int rhs);
	friend bool operator!=(const player_data& lhs, const int rhs);
	friend bool operator>(const player_data& lhs, const int rhs);
	friend bool operator<(const player_data& lhs, const int rhs);
	friend bool operator>=(const player_data& lhs, const int rhs);
	friend bool operator<=(const player_data& lhs, const int rhs);

};