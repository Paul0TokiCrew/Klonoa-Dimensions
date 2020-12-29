#pragma once



#include <vector>
#include <image.hpp>



class object {
public:
	object() { }
	~object() { }

	static std::vector<const char*> ids;
	static std::vector<image*> textures;
	static std::vector<std::pair<
		std::pair<int, int>,
		std::pair<int, int>
	>> pos;

};