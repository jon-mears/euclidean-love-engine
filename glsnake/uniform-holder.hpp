#ifndef UNIFORM_HOLDER_HPP
#define UNIFORM_HOLDER_HPP

#include <glm/glm.hpp>

#include "uniform.hpp"

class Texture2D;

class UniformHolder {
public:
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
	virtual ~UniformHolder() { }

	virtual void Upload() = 0;

	static UniformHolder* Create(Uniform* pUniform);
};

class Uniform1fHolder : public UniformHolder {
private:
	float mValue{ 0.0f };
	Uniform1f* const mcpUniform;
public:

	Uniform1fHolder(Uniform1f* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(float v0) override;
	virtual void Upload() override;
};

class Uniform2fHolder : public UniformHolder {
private:
	glm::vec2 mValue{ 0.0f };
	Uniform2f* const mcpUniform;
public:

	Uniform2fHolder(Uniform2f* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(float v0, float v1) override;
	virtual void Set(const glm::vec2& v) override;
	virtual void Upload() override;
};

class Uniform3fHolder : public UniformHolder {
private:
	glm::vec3 mValue{ 0.0f };
	Uniform3f* const mcpUniform;
public:

	Uniform3fHolder(Uniform3f* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(float v0, float v1, float v2) override;
	virtual void Set(const glm::vec3& v) override;
	virtual void Upload() override;
};

class Uniform4fHolder : public UniformHolder {
private:
	glm::vec4 mValue{ 0.0f };
	Uniform4f* const mcpUniform;
public:

	Uniform4fHolder(Uniform4f* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(float v0, float v1, float v2, float v3) override;
	virtual void Set(const glm::vec4& v) override;
	virtual void Upload() override;
};

class Uniform1iHolder : public UniformHolder {
private:
	int mValue{ 0 };
	Uniform1i* const mcpUniform;
public:

	Uniform1iHolder(Uniform1i* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(int v0) override;
	virtual void Upload() override;
};

class Uniform2iHolder : public UniformHolder {
private:
	glm::ivec2 mValue{ 0 };
	Uniform2i* const mcpUniform;
public:

	Uniform2iHolder(Uniform2i* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(int v0, int v1) override;
	virtual void Set(const glm::ivec2& v) override;
	virtual void Upload() override;
};

class Uniform3iHolder : public UniformHolder {
private:
	glm::ivec3 mValue{ 0 };
	Uniform3i* const mcpUniform;
public:

	Uniform3iHolder(Uniform3i* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(int v0, int v1, int v2) override;
	virtual void Set(const glm::ivec3& v) override;
	virtual void Upload() override;
};

class Uniform4iHolder : public UniformHolder {
private:
	glm::ivec4 mValue{ 0 };
	Uniform4i* const mcpUniform;
public:

	Uniform4iHolder(Uniform4i* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(int v0, int v1, int v2, int v3) override;
	virtual void Set(const glm::ivec4& v) override;
	virtual void Upload() override;
};

class UniformMat2Holder : public UniformHolder {
private:
	glm::mat2 mValue{ 0.0f };
	UniformMat2* const mcpUniform;
public:

	UniformMat2Holder(UniformMat2* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(const glm::mat2& matrix) override;
	virtual void Upload() override;
};

class UniformMat3Holder : public UniformHolder {
private:
	glm::mat3 mValue{ 0.0f };
	UniformMat3* const mcpUniform;
public:

	UniformMat3Holder(UniformMat3* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(const glm::mat3& matrix) override;
	virtual void Upload() override;
};

class UniformMat4Holder : public UniformHolder {
private:
	glm::mat4 mValue{ 0.0f };
	UniformMat4* const mcpUniform;
public:

	UniformMat4Holder(UniformMat4* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(const glm::mat4& matrix) override;
	virtual void Upload() override;
};

class UniformTexture2DHolder : public UniformHolder {
private:
	Texture2D* mpValue{ nullptr };
	UniformTexture2D* const mcpUniform;
public:
	UniformTexture2DHolder(UniformTexture2D* pUniform) :
		mcpUniform{ pUniform } { }
	virtual void Set(Texture2D* pTexture) override;
	virtual void Upload() override;
};
#endif