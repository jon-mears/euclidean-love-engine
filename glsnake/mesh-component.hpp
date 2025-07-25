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
	GLenum mePrimitiveType { GL_TRIANGLES };

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void ConstUpdate() const override;

	MeshComponent(GameObject* pGO);
	void SetMesh(Mesh* pMesh);
	void Enable();
	int NumVertices();
	inline void SetPrimitiveType(GLenum ePrimitiveType) { mePrimitiveType = ePrimitiveType; }
	inline GLenum GetPrimitiveType() { return mePrimitiveType; }

	inline const char* Name() const {
		return "Mesh";
	}
};
#endif