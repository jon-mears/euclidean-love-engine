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

	enum Purpose {
		MVP_MATRIX,
		M_MATRIX,
		V_MATRIX,
		P_MATRIX,
		MV_MATRIX,
		VP_MATRIX,
		NONE
	};

	std::string mName;
	Purpose mePurpose;
	Uniform(const std::string &name, GLuint loc, Purpose ePurpose);
	Uniform(std::nullptr_t null, GLuint loc) = delete;

	static std::string Encode(std::string name, GLuint loc, std::string type, 
		Uniform::Purpose mePurpose = Uniform::NONE);
	static Uniform* Decode(const std::string& code);
	static Uniform::Purpose Category(const std::string& rcName);
	virtual void Upload() = 0;

	inline Purpose GetPurpose() { return mePurpose; }

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
	float mBufValue{ 0.0f };
public:

	Uniform1f(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(float v0) override;
	virtual void Upload() override;
};

class Uniform2f : public Uniform {
private:
	glm::vec2 mValue;
	glm::vec2 mBufValue{};
public:

	Uniform2f(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(float v0, float v1) override;
	virtual void Set(const glm::vec2& v) override;
	virtual void Upload() override;
};

class Uniform3f : public Uniform {
private:
	glm::vec3 mValue;
	glm::vec3 mBufValue{};
public:

	Uniform3f(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(float v0, float v1, float v2) override;
	virtual void Set(const glm::vec3& v) override;
	virtual void Upload() override;
};

class Uniform4f : public Uniform {
private:
	glm::vec4 mValue;
	glm::vec4 mBufValue{};
public:

	Uniform4f(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(float v0, float v1, float v2, float v3) override;
	virtual void Set(const glm::vec4& v) override;
	virtual void Upload() override;
};

class Uniform1i : public Uniform {
private:
	int mValue;
	int mBufValue{};
public:

	Uniform1i(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(int v0) override;
	virtual void Upload() override;
};

class Uniform2i : public Uniform {
private:
	glm::ivec2 mValue;
	glm::ivec2 mBufValue{};
public:

	Uniform2i(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(int v0, int v1) override;
	virtual void Set(const glm::ivec2& v) override;
	virtual void Upload() override;
};

class Uniform3i : public Uniform {
private:
	glm::ivec3 mValue;
	glm::ivec3 mBufValue{};
public:

	Uniform3i(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(int v0, int v1, int v2) override;
	virtual void Set(const glm::ivec3& v) override;
	virtual void Upload() override;
};

class Uniform4i : public Uniform {
private:
	glm::ivec4 mValue;
	glm::ivec4 mBufValue{};
public:

	Uniform4i(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(int v0, int v1, int v2, int v3) override;
	virtual void Set(const glm::ivec4& v) override;
	virtual void Upload() override;
};

class UniformMat2 : public Uniform {
private:
	glm::mat2 mValue;
	glm::mat2 mBufValue{};
public:

	UniformMat2(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(const glm::mat2& matrix) override;
	virtual void Upload() override;
};

class UniformMat3 : public Uniform {
private:
	glm::mat3 mValue;
	glm::mat3 mBufValue{};
public:

	UniformMat3(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(const glm::mat3& matrix) override;
	virtual void Upload() override;
};

class UniformMat4 : public Uniform {
private:
	glm::mat4 mValue{ 1 };
	glm::mat4 mBufValue{};
public:

	UniformMat4(const std::string& name, GLuint loc, Purpose ePurpose); 
	virtual void Set(const glm::mat4& matrix) override;
	virtual void Upload() override;
};

class UniformTexture2D : public Uniform {
private:
	Texture2D* mpValue;
	Texture2D* mpBufValue{ nullptr };
public:

	UniformTexture2D(const std::string& name, GLuint loc, Purpose ePurpose);
	virtual void Set(Texture2D* pTexture) override;
	virtual void Upload() override;
};
#endif

// resource updaters?

// checks for semantic equivalence of glsl programs??