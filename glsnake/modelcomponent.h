#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H
#include "component.h"

class GameObject;
class Model;

class ModelComponent : public Component {
private:
	Model* model;
public:

	virtual void start() override;
	virtual void update() override;

	ModelComponent(GameObject* gameobject);
	void set_model(Model* m);
	void enable();
	int num_vertices();
};
#endif