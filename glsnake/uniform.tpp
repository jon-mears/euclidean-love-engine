#ifndef UNIFORM_T
#define UNIFORM_T

#include "uniform.h"
#include <glm/glm.hpp>
#include <iostream>

template<typename T>
T Uniform<T>::value() {
	return val;
}

template<typename T>
void Uniform<T>::upload(T val) {
	this->val = val;
}

#endif