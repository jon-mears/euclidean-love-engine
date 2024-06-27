#ifndef MESH_COMPONENT_HPP
#define MESH_COMPONENT_HPP
#include "component.h"

class GameObject;
class Mesh;

class MeshComponent : public Component {
private:
	Mesh* mesh;
public:

	virtual void start() override;
	virtual void update() override;

	MeshComponent(GameObject* gameobject);
	void set_mesh(Mesh* m);
	void enable();
	int num_vertices();
};
#endif