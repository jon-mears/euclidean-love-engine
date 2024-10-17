#ifndef MESH_COMPONENT_HPP
#define MESH_COMPONENT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "component.hpp"

class GameObject;
class Mesh;

class MeshComponent : public Component {
private:
	Mesh* mpMesh;
	GLenum meRenderMode{ GL_TRIANGLES };

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void ConstUpdate() const override;

	MeshComponent(GameObject* pGO);
	void SetMesh(Mesh* pMesh);
	void Enable();
	int NumVertices();
	inline void SetRenderMode(GLenum eRenderMode) { meRenderMode = eRenderMode; }
	inline GLenum GetRenderMode() { return meRenderMode; }
};
#endif