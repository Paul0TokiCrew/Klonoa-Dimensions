#define __COORDINATOR_OBJ__
#include <ECS.hpp>



template <class T>
void component_array<T>::add_data(const entity ent, const T data) {
	const std::uint32_t new_i = this->size;

	this->en_to_i[ent] = new_i;
	this->i_to_en[new_i] = ent;

	this->comp_arr = data;

	++(this->size);

}



entity entity_manager::create_entity() {
	const entity ent = this->avaible_entities.front();
	this->avaible_entities.pop();

	++(this->entity_count);

	return ent;
}

void entity_manager::destroy_entity(const entity ent) {
	this->signs[ent].reset();
	this->avaible_entities.push(ent);
	--(this->entity_count);
}



void component_manager::entity_destroyed(const entity ent) {

	for (const auto& i : this->comp_arrs) {

		const auto& comp = i.second;
		comp->entity_destroyed(ent);

	}

}



void system_manager::entity_destroyed(const entity ent) {

	for (const auto& i : this->sys) {

		const auto& s = i.second;
		s->ents.erase(ent);

	}

}

void system_manager::entity_sign_changed(const entity ent, const signature sign) {

	for (const auto& i : this->sys) {

		const auto& type = i.first;
		const auto& s = i.second;
		const auto& s_sign = this->signs[type];

		if ((sign & s_sign) == s_sign) {
			s->ents.insert(ent);

		} else {
			s->ents.erase(ent);

		}

	}

}



void coordinator::init() {
	static bool initialized = false;

	if (initialized)
		return;

	initialized = true;

	this->ent_man = std::make_unique<entity_manager>();
	this->comp_man = std::make_unique<component_manager>();
	this->sys_man = std::make_unique<system_manager>();

}

void coordinator::destroy_ent(const entity ent) {
	this->ent_man->destroy_entity(ent);
	this->comp_man->entity_destroyed(ent);
	this->sys_man->entity_destroyed(ent);
}

template <class T>
void coordinator::add_comp(const entity ent, const T comp) {
	signature sign = this->ent_man->get_signature(ent);
	sign.set(this->comp_man->get_component_type<T>(), true);

	this->comp_man->add_component<T>(ent, comp);
	this->ent_man->set_signature(ent, sign);
	this->sys_man->entity_sign_changed(ent, sign);
}

template <class T>
void coordinator::remove_comp(const entity ent) {
	signature sign = this->ent_man->get_signature(ent);
	sign.set(this->comp_man->get_component_type<T>(), false);

	this->comp_man->remove_component<T>(ent);
	this->ent_man->set_signature(ent, sign);
	this->sys_man->entity_sign_changed(ent, sign);
}