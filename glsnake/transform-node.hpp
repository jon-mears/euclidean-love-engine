#ifndef TRANSFORM_NODE_HPP
#define TRANSFORM_NODE_HPP

#include "transform.hpp"

#include <glm/glm.hpp>

class TransformNode {

public:
	TransformNode(Transform* pTransform);

	Transform* GetTransform();

	glm::mat4 Result();
	
private:
	Transform* mpTransform;
	int mChangeCount;

	glm::mat4 mResult;

	TransformNode* mpPrev;
};
#endif