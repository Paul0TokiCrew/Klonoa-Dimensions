#pragma once



#include <cstdint>



#define MAX_ENTITES 1000
#define MAX_COMPONENTS 500



using entity = std::uint16_t;
using component_id = std::uint16_t;



inline component_id get_new_id() {
	static component_id new_id = 0;
	return new_id++;
}

template <class T>
inline component_id get_id() {
	static component_id id = get_new_id();
	return id;
}