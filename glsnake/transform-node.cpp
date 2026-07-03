#include "transform-node.hpp"

TransformNode::TransformNode(Transform* pTransform) :
	mpTransform{ pTransform }, mChangeCount{ 0 }, mResult{ 1 },
	mpPrev{ nullptr } { };

Transform* TransformNode::GetTransform() {
	return mpTransform;
}

glm::mat4 TransformNode::Result() {
	if (mChangeCount == mpTransform->GetChangeCount()) return mResult;
	if (mpPrev != nullptr) {
		mResult = mpTransform->ApplyToRHSOf(mpPrev->Result());
	}
	else {
		mResult = mpTransform->ApplyToRHSOf(glm::mat4{ 1 });
	}

	mChangeCount = mpTransform->GetChangeCount();
	return mResult;
}