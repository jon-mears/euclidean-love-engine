#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertexdata.h"

enum class Attribute {
	NONE = 1,
	POSITION = 2, 
	VERTEX_COLOR = 4,
	TEXTURE_COORD = 8
};

class Model {
private:
	GLuint vao;

	std::map<int, VertexData> mAttribLoc2VData; // attribute loc to data
	std::map<Attribute, VertexData> mAttribType2VData; // attribute type to data

	std::vector<float> collect_data();

	int _num_vertices = -1;	
	int _position_attrib = -1;
	int _vertex_color_attrib = -1;

	std::string mName;

public:
	void vertex_attrib(int attrib_loc, VertexData vdata, Attribute attrib=Attribute::NONE);
	void vertex_attrib(Attribute attrib, VertexData vdata);
	void compile();
	void enable();
	int num_vertices();
	VertexData get_attrib(Attribute attrib);

	std::string& name();
	void name(const std::string& name);
};

#endif