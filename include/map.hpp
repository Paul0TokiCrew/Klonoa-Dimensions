#pragma once



#include <string>



class map {
private:
	std::string lvl;

public:
	map(std::string lvl = "") :
		lvl(lvl) { }
	~map() { }

	std::string get_lvl() const { return this->lvl; }
	void set_lvl(const std::string lvl) { this->lvl = lvl; }

};