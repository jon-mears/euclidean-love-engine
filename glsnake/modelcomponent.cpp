#include "mesh_component.hpp"
#include "gameobject.h"
#include "component.h"
#include "mesh.h"

MeshComponent::MeshComponent(GameObject* gameobject) : Component(gameobject), mesh(NULL) { }

void MeshComponent::set_mesh(Mesh* m) {
	mesh = m;
}

void MeshComponent::enable() {
	mesh->enable();
}

int MeshComponent::num_vertices() {
	return mesh->num_vertices();
}

void MeshComponent::start() { }
void MeshComponent::update() { }