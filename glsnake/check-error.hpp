#ifndef CHECK_ERROR_HPP
#define CHECK_ERROR_HPP

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void LogErrors_impl(const char* file, int line);

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam);

#ifndef NDEBUG
#define LogErrors() LogErrors_impl(__FILE__, __LINE__)
#else
#define LogErrors() 
#endif

#endif