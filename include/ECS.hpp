#pragma once



#include <cstdint>
#include <memory>
#include <typeinfo>
#include <utility>
#include <bitset>
#include <array>
#include <queue>
#include <unordered_map>
#include <set>



#define MAX_ENTITIES 1000
#define MAX_COMPONENTS 500



using entity = std::uint16_t;
using component = std::uint16_t;
using signature = std::bitset<MAX_COMPONENTS>;



struct system { std::set<entity> ents; };



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

	void add_data(const entity ent, const T data) {
		const std::uint32_t new_i = this->size;

		this->en_to_i[ent] = new_i;
		this->i_to_en[new_i] = ent;

		this->comp_arr[new_i] = data;

		++(this->size);

	}
	void remove_data(const entity ent) {
		const std::uint32_t removed_i = this->en_to_i[ent];
		const std::uint32_t last_i = this->size - 1;
		const entity last_en = this->i_to_en[last_i];

		this->comp_arr[removed_i] = this->comp_arr[last_i];

		this->en_to_i[last_en] = removed_i;
		this->i_to_en[removed_i] = last_en;

		this->en_to_i.erase(ent);
		this->i_to_en.erase(last_i);

		--(this->size);
	}

	void entity_destroyed(const entity ent) override {
		if (this->en_to_i.find(ent) != this->en_to_i.end())
		this->remove_data(ent);

	}

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
	void register_component() {
		const char* name = typeid(T).name();
		this->comp_types.emplace(name, this->next_comp_type++);
		this->comp_arrs.emplace(name, std::make_shared<component_array<T>>());
	}

	template <class T>
	component get_component_type() { return this->comp_types[typeid(T).name()]; }

	template <class T>
	void add_component(const entity ent, const T comp) { this->get_component_array<T>()->add_data(ent, comp); }

	template <class T>
	void remove_component(const entity ent) { this->get_component_array<T>()->remove_data(ent); }

	template <class T>
	T& get_component(const entity ent) { return this->get_component_array<T>()->get_data(ent); }

	void entity_destroyed(const entity ent);

};




class system_manager {
private:
	std::unordered_map<const char*, signature> signs;
	std::unordered_map<const char*, std::shared_ptr<struct system>> sys;

public:
	system_manager() :
	signs { }, sys { } { }
	~system_manager() { }

	template <class T>
	std::shared_ptr<T> register_system() {
		const char* name = typeid(T).name();
		std::shared_ptr<T> s = std::make_shared<T>();

		this->sys.emplace(name, s);
		return s;
	}

	template <class T>
	void set_sign(const signature sign) { this->signs.emplace(typeid(T).name(), sign); }

	void entity_destroyed(const entity ent);
	void entity_sign_changed(const entity ent, const signature sign);

};




class coordinator {
private:
	std::unique_ptr<entity_manager> ent_man;
	std::unique_ptr<component_manager> comp_man;
	std::unique_ptr<system_manager> sys_man;

public:
	coordinator() :
	ent_man(nullptr), comp_man(nullptr), sys_man(nullptr) { }
	~coordinator() { }

	void init();

	entity create_ent() { return this->ent_man->create_entity(); }
	void destroy_ent(const entity ent);



	template <class T>
	void register_comp() { this->comp_man->register_component<T>(); }

	template <class T>
	void add_comp(const entity ent, const T comp) {
		signature sign = this->ent_man->get_signature(ent);
		sign.set(this->comp_man->get_component_type<T>(), true);

		this->comp_man->add_component<T>(ent, comp);
		this->ent_man->set_signature(ent, sign);
		this->sys_man->entity_sign_changed(ent, sign);
	}

	template <class T>
	void remove_comp(const entity ent) {
		signature sign = this->ent_man->get_signature(ent);
		sign.set(this->comp_man->get_component_type<T>(), false);

		this->comp_man->remove_component<T>(ent);
		this->ent_man->set_signature(ent, sign);
		this->sys_man->entity_sign_changed(ent, sign);
	}

	template <class T>
	T& get_comp(const entity ent) { return this->comp_man->get_component<T>(ent); }

	template <class T>
	component get_comp_type() { return this->comp_man->get_component_type<T>(); }



	template<typename T>
	std::shared_ptr<T> register_sys() { return this->sys_man->register_system<T>(); }

	template<typename T>
	void set_sys_signature(const signature sign) { this->sys_man->set_sign<T>(sign); }

};

#ifndef __COORDINATOR_OBJ__
	extern coordinator crd;
#else
	coordinator crd;
#endif