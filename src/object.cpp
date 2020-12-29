#include <vector>
#include <image.hpp>
#include <object.hpp>



std::vector<const char*> object::ids;
std::vector<image*> object::textures;
std::vector<std::pair<
	std::pair<int, int>,
	std::pair<int, int>
>> object::pos;