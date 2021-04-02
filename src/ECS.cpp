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