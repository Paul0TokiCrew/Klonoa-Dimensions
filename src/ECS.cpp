#define __COORDINATOR_OBJ__
#include <ECS.hpp>



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