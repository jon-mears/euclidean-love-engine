#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP

#include "transform.hpp"

#include <glm/glm.hpp>

class Translate : public Transform {
public:
	Translate();

	void Set(glm::vec3 const& translation);
	glm::vec3 Get();

	void SetX(float x);
	float GetX();

	void SetY(float y);
	float GetY();

	void SetZ(float z);
	float GetZ();

	glm::mat4 ApplyToRHSOf(glm::mat4 const& lhs) override;
private:
	glm::vec3 mTranslation;
};
#endif