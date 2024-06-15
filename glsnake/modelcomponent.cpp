#include "modelcomponent.h"
#include "gameobject.h"
#include "component.h"
#include "model.h"

ModelComponent::ModelComponent(GameObject* gameobject) : Component(gameobject), model(nullptr) { }

void ModelComponent::set_model(Model* m) {
	model = m;
}

void ModelComponent::enable() {
	model->enable();
}

int ModelComponent::num_vertices() {
	return model->num_vertices();
}

void ModelComponent::start() { }
void ModelComponent::update() { }