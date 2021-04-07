#pragma once



#include <cstdint>
#include <memory>
#include <typeinfo>
#include <utility>
#include <bitset>
#include <array>
#include <queue>
#include <unordered_map>



#define MAX_ENTITIES 1000
#define MAX_COMPONENTS 500



using entity = std::uint16_t;
using component = std::uint16_t;
using signature = std::bitset<MAX_COMPONENTS>;



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

	T& get_data(const entity ent) /* const */ { return this->comp_arr[this->en_to_i[ent]]; }

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



class component_manager {
private:
	std::unordered_map<const char*, component> comp_types;
	std::unordered_map<const char*, std::shared_ptr<i_component_array>> comp_arrs;
	component next_comp_type;

	template<class T>
	std::shared_ptr<component_array<T>> get_component_array() {
		return std::static_pointer_cast<component_array<T>>(this->comp_arrs[typeid(T).name()]);
	}

public:
	component_manager() :
		comp_types { }, comp_arrs { }, next_comp_type(0) { }
	~component_manager() { }

	template <class T>
	void register_component();

	template <class T>
	component get_component_type() /* const */ { return this->comp_types[typeid(T).name()]; }

	template <class T>
	void add_component(entity ent, T comp) { this->get_component_array<T>()->add_data(ent, comp); }

	template <class T>
	void remove_component(entity ent) { this->get_component_array<T>()->remove_data(ent); }

	template <class T>
	T& get_component(entity ent) /* const */ { this->get_component_array<T>()->get_data(ent); }

	void entity_destroyed(entity ent);

};