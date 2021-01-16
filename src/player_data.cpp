#include <player_data.hpp>



player_data& player_data::operator=(const int new_data) {
	if (!(new_data < this->min || new_data > this->max))
		this->current_data = new_data;

	return *this;
}

bool operator==(const player_data& lhs, const int rhs) {
	if (lhs.current_data == rhs)
		return true;

	return false;
}

bool operator!=(const player_data& lhs, const int rhs) {
	if (lhs.current_data != rhs)
		return true;

	return false;
}

bool operator>(const player_data& lhs, const int rhs) {
	if (lhs.current_data > rhs)
		return true;

	return false;
}

bool operator<(const player_data& lhs, const int rhs) {
	if (lhs.current_data < rhs)
		return true;

	return false;
}

bool operator>=(const player_data& lhs, const int rhs) {
	if (lhs.current_data >= rhs)
		return true;

	return false;
}

bool operator<=(const player_data& lhs, const int rhs) {
	if (lhs.current_data <= rhs)
		return true;

	return false;
}