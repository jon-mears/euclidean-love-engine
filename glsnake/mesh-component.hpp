#ifndef MESH_COMPONENT_HPP
#define MESH_COMPONENT_HPP
#include "component.hpp"

class GameObject;
class Mesh;

class MeshComponent : public Component {
private:
	Mesh* mpMesh;
public:

	virtual void Start() override;
	virtual void Update() override;
	virtual void ConstUpdate() const override;

	MeshComponent(GameObject* pGO);
	void SetMesh(Mesh* pMesh);
	void Enable();
	int NumVertices();
};
#endif