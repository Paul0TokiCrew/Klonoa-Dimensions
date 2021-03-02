#include <vec2f.hpp>



void vec2f::move(float x_speed, float y_speed) {
	this->x += x_speed;
	this->y += y_speed;
}

float vec2f::get_length() const {
	return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
}

float vec2f::get_length_sqr() const {
	return std::pow(this->x, 2) + std::pow(this->y, 2);
}

vec2f vec2f::normalize() const {
	vec2f vec = vec2f(this->x / this->get_length(), this->y / this->get_length());
	return vec;
}

float vec2f::get_dot_product(const vec2f other) const  {
	vec2f ent1 = this->normalize(),
		ent2 = other.normalize();

	return ent1.x * ent2.x + ent1.y * ent2.y;
}

vec2f vec2f::operator+(const vec2f other) const {
	vec2f vec = vec2f(this->x + other.x, this->y + other.y);
	return vec;
}

vec2f vec2f::operator-(const vec2f other) const {
	vec2f vec = vec2f(this->x - other.x, this->y - other.y);
	return vec;
}

vec2f vec2f::operator*(const vec2f other) const {
	vec2f vec = vec2f(this->x * other.x, this->y * other.y);
	return vec;
}

vec2f vec2f::operator/(const vec2f other) const {
	vec2f vec = vec2f(this->x / other.x, this->y / other.y);
	return vec;
}

vec2f& vec2f::operator=(const vec2f new_vec) {
	this->x = new_vec.x;
	this->y = new_vec.y;
	return *this;
}



bool operator==(const vec2f lhs, const vec2f rhs) {
	if (lhs.x == rhs.x && lhs.y == rhs.y)
		return true;

	return false;
}

bool operator!=(const vec2f lhs, const vec2f rhs) {
	if (lhs.x != rhs.x && lhs.y != rhs.y)
		return true;

	return false;
}

bool operator>(const vec2f lhs, const vec2f rhs) {
	if (lhs.x > rhs.x && lhs.y > rhs.y)
		return true;

	return false;
}

bool operator<(const vec2f lhs, const vec2f rhs) {
	if (lhs.x < rhs.x && lhs.y < rhs.y)
		return true;

	return false;
}

bool operator>=(const vec2f lhs, const vec2f rhs) {
	if (lhs.x >= rhs.x && lhs.y >= rhs.y)
		return true;

	return false;
}

bool operator<=(const vec2f lhs, const vec2f rhs) {
	if (lhs.x <= rhs.x && lhs.y <= rhs.y)
		return true;

	return false;
}

std::ostream& operator<<(std::ostream& os, const vec2f vec) {
	os << "{ " << vec.x << ", " << vec.y << " }";
	return os;
}

std::wostream& operator<<(std::wostream& wos, const vec2f vec) {
	wos << "{ " << vec.x << ", " << vec.y << " }";
	return wos;
}