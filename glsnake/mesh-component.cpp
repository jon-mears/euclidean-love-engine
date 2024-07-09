#include "mesh-component.hpp"
#include "game-object.hpp"
#include "component.hpp"
#include "mesh.hpp"

MeshComponent::MeshComponent(GameObject* pGO) : Component{pGO}, mpMesh{nullptr} { }

void MeshComponent::SetMesh(Mesh* pMesh) {
	mpMesh = pMesh;
}

void MeshComponent::Enable() {
	mpMesh->Enable();
}

int MeshComponent::NumVertices() {
	return mpMesh->NumVertices();
}

void MeshComponent::Start() { }
void MeshComponent::Update() { }