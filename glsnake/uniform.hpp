#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Texture2D;

class Uniform {
protected:
	GLuint mLoc;
public:
	std::string mName;
	Uniform(const std::string &name, GLuint loc);
	Uniform(std::nullptr_t null, GLuint loc) = delete;

	static std::string Encode(std::string name, GLuint loc, std::string type);
	static Uniform* Decode(const std::string& code);
	virtual void Upload() = 0;

	virtual void Set(float v0);
	virtual void Set(float v0, float v1);
	virtual void Set(const glm::vec2& v);
	virtual void Set(float v0, float v1, float v2);
	virtual void Set(const glm::vec3& v);
	virtual void Set(float v0, float v1, float v2, float v3);
	virtual void Set(const glm::vec4& v);
	virtual void Set(int v0);
	virtual void Set(int v0, int v1);
	virtual void Set(const glm::ivec2& v);
	virtual void Set(int v0, int v1, int v2);
	virtual void Set(const glm::ivec3& v);
	virtual void Set(int v0, int v1, int v2, int v3);
	virtual void Set(const glm::ivec4& v);
	virtual void Set(const glm::mat2& matrix);
	virtual void Set(const glm::mat3& matrix);
	virtual void Set(const glm::mat4& matrix);
	virtual void Set(Texture2D* tex);
	virtual ~Uniform() { }
};

class Uniform1f : public Uniform {
private:
	float mValue{ 0.0f };
public:

	Uniform1f(const std::string& name, GLuint loc);
	virtual void Set(float v0) override;
	virtual void Upload() override;
};

class Uniform2f : public Uniform {
private:
	glm::vec2 mValue;
public:

	Uniform2f(const std::string& name, GLuint loc);
	virtual void Set(float v0, float v1) override;
	virtual void Set(const glm::vec2& v) override;
	virtual void Upload() override;
};

class Uniform3f : public Uniform {
private:
	glm::vec3 mValue;
public:

	Uniform3f(const std::string& name, GLuint loc);
	virtual void Set(float v0, float v1, float v2) override;
	virtual void Set(const glm::vec3& v) override;
	virtual void Upload() override;
};

class Uniform4f : public Uniform {
private:
	glm::vec4 mValue;
public:

	Uniform4f(const std::string& name, GLuint loc);
	virtual void Set(float v0, float v1, float v2, float v3) override;
	virtual void Set(const glm::vec4& v) override;
	virtual void Upload() override;
};

class Uniform1i : public Uniform {
private:
	int mValue;
public:

	Uniform1i(const std::string& name, GLuint loc);
	virtual void Set(int v0) override;
	virtual void Upload() override;
};

class Uniform2i : public Uniform {
private:
	glm::ivec2 mValue;
public:

	Uniform2i(const std::string& name, GLuint loc);
	virtual void Set(int v0, int v1) override;
	virtual void Set(const glm::ivec2& v) override;
	virtual void Upload() override;
};

class Uniform3i : public Uniform {
private:
	glm::ivec3 mValue;
public:

	Uniform3i(const std::string& name, GLuint loc);
	virtual void Set(int v0, int v1, int v2) override;
	virtual void Set(const glm::ivec3& v) override;
	virtual void Upload() override;
};

class Uniform4i : public Uniform {
private:
	glm::ivec4 mValue;
public:

	Uniform4i(const std::string& name, GLuint loc);
	virtual void Set(int v0, int v1, int v2, int v3) override;
	virtual void Set(const glm::ivec4& v) override;
	virtual void Upload() override;
};

class UniformMat2 : public Uniform {
private:
	glm::mat2 mValue;
public:

	UniformMat2(const std::string& name, GLuint loc);
	virtual void Set(const glm::mat2& matrix) override;
	virtual void Upload() override;
};

class UniformMat3 : public Uniform {
private:
	glm::mat3 mValue;
public:

	UniformMat3(const std::string& name, GLuint loc);
	virtual void Set(const glm::mat3& matrix) override;
	virtual void Upload() override;
};

class UniformMat4 : public Uniform {
private:
	glm::mat4 mValue{ 1 };
public:

	UniformMat4(const std::string& name, GLuint loc); 
	virtual void Set(const glm::mat4& matrix) override;
	virtual void Upload() override;
};

class UniformTexture2D : public Uniform {
private:
	Texture2D* mpValue;
public:

	UniformTexture2D(const std::string& name, GLuint loc);
	virtual void Set(Texture2D* pTexture) override;
	virtual void Upload() override;
};
#endif