#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>

class Transform {
public:
	Transform();

	int GetChangeCount();

	virtual glm::mat4 ApplyToRHSOf(glm::mat4 const& lhs) = 0;

protected:
	int mChangeCount;
};

#endif