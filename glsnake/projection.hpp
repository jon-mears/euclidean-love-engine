#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Projection {
public:
	~Projection() { }
	virtual glm::mat4 ProjectionMatrix() = 0;
};

class Orthographic : public Projection {
private:
	float mLeft, mRight, mTop, mBottom, mNear{ 0.1 }, mFar{ 100 };
public:
	Orthographic();
	virtual glm::mat4 ProjectionMatrix() override;
};

class Perspective : public Projection {
private:
	float mFOVY{ 45.0f }, mAspect{ 0.0f }, mZNear{ 0.01f }, mZFar{ 100.0f };
public:
	Perspective();
	virtual glm::mat4 ProjectionMatrix() override;
};

class NoProjection : public Projection {
public:
	virtual glm::mat4 ProjectionMatrix() override;
};

class AspectProjection : public Projection {
public:
	virtual glm::mat4 ProjectionMatrix() override;
};
#endif