#include <ECS.hpp>



template <class T>
void component_array<T>::add_data(const entity ent, const T data) {
	const std::uint32_t new_i = this->size;

	this->en_to_i[ent] = new_i;
	this->i_to_en[new_i] = ent;

	this->comp_arr = data;

	++(this->size);

}

template <class T>
void component_array<T>::remove_data(const entity ent) {
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

template <class T>
void component_array<T>::entity_destroyed(const entity ent) {
	if (this->en_to_i.find(ent) != this->en_to_i.end())
		this->remove_data(ent);

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



template <class T>
void component_manager::register_component() {
	const char* name = typeid(T).name();
	this->comp_types.emplace(name, this->next_comp_type++);
	this->comp_arrs.emplace(name, std::make_shared<component_array<T>>());
}

void component_manager::entity_destroyed(entity ent) {

	for (const auto& i : this->comp_arrs) {

		const auto& comp = i.second;
		comp->entity_destroyed(ent);

	}

}




template <class T>
std::shared_ptr<T> system_manager::register_system() {
	const char name = typeid(T).name();
	std::shared_ptr<T> s = std::make_shared<T>();

	this->sys.emplace(name, s);
	return s;
}

void system_manager::entity_destroyed(entity ent) {

	for (const auto& i : this->sys) {

		const auto& s = i.second;
		s->ents.erase(ent);

	}

}

void system_manager::entity_sign_changed(entity ent, signature sign) {

	for (const auto& i : this->sys) {

		const auto& type = i.first;
		const auto& s = i.second;
		const auto& s_sign = this->sign[type];

		if ((sign & s_sign) == s_sign) {
			s->ents.insert(entity);

		} else {
			s->ents.erase(entity);

		}

	}

}