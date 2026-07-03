#include "transform.hpp"

Transform::Transform() : mChangeCount{ 0 } { };

int Transform::GetChangeCount() {
	return mChangeCount;
}