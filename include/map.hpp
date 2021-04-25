#pragma once



#include <string>



class map {
private:
	std::string lvl;

public:
	map(std::string lvl = "") :
		lvl(lvl) { }
	~map() { }

};