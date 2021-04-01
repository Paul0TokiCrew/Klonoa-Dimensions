#pragma once



#include <cstdint>
#include <bitset>
#include <array>
#include <queue>



#define MAX_ENTITIES 1000
#define MAX_COMPONENTS 500



using entity = std::uint16_t;
using component_id = std::uint16_t;
using signature = std::bitset<MAX_COMPONENTS>;



inline component_id get_new_id() {
	static component_id new_id = 0;
	return new_id++;
}

template <class T>
inline component_id get_id() {
	static component_id id = get_new_id();
	return id;
}



class entity_manager {
private:
	std::uint32_t entity_count;
	std::queue<entity> avaible_entities;

	std::array<signature, MAX_ENTITIES> signs;

public:
	entity_manager() :
		entity_count(0), avaible_entities { }, signs { } {
		for (entity i = 0; i < MAX_ENTITIES; ++i)
			this->avaible_entities.push(i);

	}
	~entity_manager() { }

	void set_signature(const entity ent, const signature sign) { this->signs[ent] = sign; }
	signature get_signature(const entity ent) { return this->signs[ent]; }

	entity create_entity();
	void destroy_entity(entity ent);

};