#ifndef UNIFORM_H
#define UNIFORM_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Texture2D;

class Uniform {
protected:
	GLuint loc;
public:
	std::string name;
	Uniform(const std::string &name, GLuint loc);

	static std::string encode(std::string name, GLuint loc, std::string type);
	static Uniform* decode(const std::string& code);
	virtual void upload() = 0;

	virtual void set(float v0);
	virtual void set(float v0, float v1);
	virtual void set(const glm::vec2& v);
	virtual void set(float v0, float v1, float v2);
	virtual void set(const glm::vec3& v);
	virtual void set(float v0, float v1, float v2, float v3);
	virtual void set(const glm::vec4& v);
	virtual void set(int v0);
	virtual void set(int v0, int v1);
	virtual void set(const glm::ivec2& v);
	virtual void set(int v0, int v1, int v2);
	virtual void set(const glm::ivec3& v);
	virtual void set(int v0, int v1, int v2, int v3);
	virtual void set(const glm::ivec4& v);
	virtual void set(const glm::mat2& matrix);
	virtual void set(const glm::mat3& matrix);
	virtual void set(const glm::mat4& matrix);
	virtual void set(Texture2D* tex);
	virtual ~Uniform() = default;
};

class Uniform1f : public Uniform {
private:
	float v0;
public:

	Uniform1f(const std::string& name, GLuint loc);
	virtual void set(float v0) override;
	virtual void upload() override;
};

class Uniform2f : public Uniform {
private:
	glm::vec2 v;
public:

	Uniform2f(const std::string& name, GLuint loc);
	virtual void set(float v0, float v1) override;
	virtual void set(const glm::vec2& v) override;
	virtual void upload() override;
};

class Uniform3f : public Uniform {
private:
	glm::vec3 v;
public:

	Uniform3f(const std::string& name, GLuint loc);
	virtual void set(float v0, float v1, float v2) override;
	virtual void set(const glm::vec3& v) override;
	virtual void upload() override;
};

class Uniform4f : public Uniform {
private:
	glm::vec4 v;
public:

	Uniform4f(const std::string& name, GLuint loc);
	virtual void set(float v0, float v1, float v2, float v3) override;
	virtual void set(const glm::vec4& v) override;
	virtual void upload() override;
};

class Uniform1i : public Uniform {
private:
	int v0;
public:

	Uniform1i(const std::string& name, GLuint loc);
	virtual void set(int v0) override;
	virtual void upload() override;
};

class Uniform2i : public Uniform {
private:
	glm::ivec2 v;
public:

	Uniform2i(const std::string& name, GLuint loc);
	virtual void set(int v0, int v1) override;
	virtual void set(const glm::ivec2& v) override;
	virtual void upload() override;
};

class Uniform3i : public Uniform {
private:
	glm::ivec3 v;
public:

	Uniform3i(const std::string& name, GLuint loc);
	virtual void set(int v0, int v1, int v2) override;
	virtual void set(const glm::ivec3& v) override;
	virtual void upload() override;
};

class Uniform4i : public Uniform {
private:
	glm::ivec4 v;
public:

	Uniform4i(const std::string& name, GLuint loc);
	virtual void set(int v0, int v1, int v2, int v3) override;
	virtual void set(const glm::ivec4& v) override;
	virtual void upload() override;
};

class UniformMat2 : public Uniform {
private:
	glm::mat2 m;
public:

	UniformMat2(const std::string& name, GLuint loc);
	virtual void set(const glm::mat2& matrix) override;
	virtual void upload() override;
};

class UniformMat3 : public Uniform {
private:
	glm::mat3 m;
public:

	UniformMat3(const std::string& name, GLuint loc);
	virtual void set(const glm::mat3& matrix) override;
	virtual void upload() override;
};

class UniformMat4 : public Uniform {
private:
	glm::mat4 m;
public:

	UniformMat4(const std::string& name, GLuint loc); 
	virtual void set(const glm::mat4& matrix) override;
	virtual void upload() override;
};

class UniformTexture2D : public Uniform {
private:
	Texture2D* t;
public:

	UniformTexture2D(const std::string& name, GLuint loc);
	virtual void set(Texture2D* tex) override;
	virtual void upload() override;
};
#endif