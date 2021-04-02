#pragma once



#include <cstdint>
#include <bitset>
#include <array>
#include <queue>
#include <unordered_map>



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
	const static component_id id = get_new_id();
	return id;
}



class i_component_array {
public:
	i_component_array() { }
	virtual ~i_component_array() { }

	virtual void entity_destroyed(const entity ent) = 0;

};

template <class T>
class component_array : public i_component_array {
private:
	std::array<T, MAX_ENTITIES> comp_arr;

	std::unordered_map<entity, std::uint32_t> en_to_i;
	std::unordered_map<std::uint32_t, entity> i_to_en;

	std::uint32_t size;

public:
	component_array() :
		comp_arr { }, en_to_i { }, i_to_en { }, size(0) { }
	~component_array() { }

	T& get_data(const entity ent) { return this->comp_arr[this->en_to_i[ent]]; }

	void add_data(const entity ent, const T data);
	void remove_data(const entity ent);

	void entity_destroyed(const entity ent) override;

};



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
	signature get_signature(const entity ent) const { return this->signs[ent]; }

	entity create_entity();
	void destroy_entity(const entity ent);

};