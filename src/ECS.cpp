#include <ECS.hpp>



template <class T>
void component_array<T>::entity_destroyed(entity ent) {
	if (this->en_to_i.find(ent) != this->en_to_i.end()) { }
		//this->remove_data(ent);

}



entity entity_manager::create_entity() {
	entity ent = this->avaible_entities.front();
	this->avaible_entities.pop();

	++(this->entity_count);

	return ent;
}

void entity_manager::destroy_entity(entity ent) {
	this->signs[ent].reset();
	this->avaible_entities.push(ent);
	--(this->entity_count);
}