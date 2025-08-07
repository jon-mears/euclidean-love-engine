#include <iostream>

#include "uniform.hpp"
#include "uniform-holder.hpp"

// static
UniformHolder* UniformHolder::Create(Uniform* pUniform) {
	switch (pUniform->GetType()) {
	case Uniform::FLOAT:
		return new Uniform1fHolder(dynamic_cast<Uniform1f*>(pUniform));
	case Uniform::VEC2:
		return new Uniform2fHolder(dynamic_cast<Uniform2f*>(pUniform));
	case Uniform::VEC3:
		return new Uniform3fHolder(dynamic_cast<Uniform3f*>(pUniform));
	case Uniform::VEC4:
		return new Uniform4fHolder(dynamic_cast<Uniform4f*>(pUniform));
	case Uniform::INT:
		return new Uniform1iHolder(dynamic_cast<Uniform1i*>(pUniform));
	case Uniform::IVEC2:
		return new Uniform2iHolder(dynamic_cast<Uniform2i*>(pUniform));
	case Uniform::IVEC3:
		return new Uniform3iHolder(dynamic_cast<Uniform3i*>(pUniform));
	case Uniform::IVEC4:
		return new Uniform4iHolder(dynamic_cast<Uniform4i*>(pUniform));
	case Uniform::MAT2:
		return new UniformMat2Holder(dynamic_cast<UniformMat2*>(pUniform));
	case Uniform::MAT3:
		return new UniformMat3Holder(dynamic_cast<UniformMat3*>(pUniform));
	case Uniform::MAT4:
		return new UniformMat4Holder(dynamic_cast<UniformMat4*>(pUniform));
	case Uniform::SAMPLER2D:
		return new UniformTexture2DHolder(dynamic_cast<UniformTexture2D*>(pUniform));
	default:
		std::cerr << "type not yet implemented" << std::endl;
		std::exit(-1);
	}
}

void UniformHolder::Set(float v0) {
	throw "ERROR :: CANNOT SET TO FLOAT";
}

void UniformHolder::Set(float v0, float v1) {
	throw "ERROR :: CANNOT SET TO FLOAT2";
}

void UniformHolder::Set(const glm::vec2& v) {
	throw "ERROR :: CANNOT SET TO FLOAT2";
}

void UniformHolder::Set(float v0, float v1, float v2) {
	throw "ERROR :: CANNOT SET TO FLOAT3";
}

void UniformHolder::Set(const glm::vec3& v) {
	throw "ERROR :: CANNOT SET TO FLOAT3";
}

void UniformHolder::Set(float v0, float v1, float v2, float v3) {
	throw "ERROR :: CANNOT SET TO FLOAT4";
}

void UniformHolder::Set(const glm::vec4& v) {
	throw "ERROR :: CANNOT SET TO FLOAT4";
}

void UniformHolder::Set(int v0) {
	throw "ERROR :: CANNOT SET TO INT";
}

void UniformHolder::Set(int v0, int v1) {
	throw "ERROR :: CANNOT SET TO INT2";
}

void UniformHolder::Set(const glm::ivec2& v) {
	throw "ERROR :: CANNOT SET TO INT2";
}

void UniformHolder::Set(int v0, int v1, int v2) {
	throw "ERROR :: CANNOT SET TO INT3";
}

void UniformHolder::Set(const glm::ivec3& v) {
	throw "ERROR :: CANNOT SET TO INT3";
}

void UniformHolder::Set(int v0, int v1, int v2, int v3) {
	throw "ERROR :: CANNOT SET TO INT4";
}

void UniformHolder::Set(const glm::ivec4& v) {
	throw "ERROR :: CANNOT SET TO INT4";
}

void UniformHolder::Set(const glm::mat2& m) {
	throw "ERROR :: CANNOT SET TO MAT2";
}

void UniformHolder::Set(const glm::mat3& m) {
	throw "ERROR :: CANNOT SET TO MAT3";
}

void UniformHolder::Set(const glm::mat4& m) {
	std::cerr << "can't Set uniform to matrix4!" << std::endl;
	exit(-1);
}

void UniformHolder::Set(Texture2D* tex) {
	std::cerr << "can't Set uniform to texture2D!" << std::endl;
	std::exit(-1);
}

void Uniform1fHolder::Set(float value) {
	mValue = value;
}

void Uniform1fHolder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void Uniform2fHolder::Set(float value1, float value2) {
	mValue = glm::vec2{ value1, value2 };
}

void Uniform2fHolder::Set(const glm::vec2& rcValue) {
	mValue = rcValue;
}

void Uniform2fHolder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void Uniform3fHolder::Set(float value1, float value2, float value3) {
	mValue = glm::vec3{ value1, value2, value3 };
}

void Uniform3fHolder::Set(const glm::vec3& rcValue) {
	mValue = rcValue;
}

void Uniform3fHolder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void Uniform4fHolder::Set(float value1, float value2, float value3, float value4) {
	mValue = glm::vec4{ value1, value2, value3, value4 };
}

void Uniform4fHolder::Set(const glm::vec4& rcValue) {
	mValue = rcValue;
}

void Uniform4fHolder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void Uniform1iHolder::Set(int value) {
	mValue = value;
}

void Uniform1iHolder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void Uniform2iHolder::Set(int value1, int value2) {
	mValue = glm::ivec2{ value1, value2 };
}

void Uniform2iHolder::Set(const glm::ivec2& rcValue) {
	mValue = rcValue;
}

void Uniform2iHolder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void Uniform3iHolder::Set(int value1, int value2, int value3) {
	mValue = glm::ivec3{ value1, value2, value3 };
}

void Uniform3iHolder::Set(const glm::ivec3& rcValue) {
	mValue = rcValue;
}

void Uniform3iHolder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void Uniform4iHolder::Set(int value1, int value2, int value3, int value4) {
	mValue = glm::ivec4{ value1, value2, value3, value4 };
}

void Uniform4iHolder::Set(const glm::ivec4& rcValue) {
	mValue = rcValue;
}

void Uniform4iHolder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void UniformMat2Holder::Set(const glm::mat2& rcValue) {
	mValue = rcValue;
}

void UniformMat2Holder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void UniformMat3Holder::Set(const glm::mat3& rcValue) {
	mValue = rcValue;
}

void UniformMat3Holder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void UniformMat4Holder::Set(const glm::mat4& rcValue) {
	mValue = rcValue;
}

void UniformMat4Holder::Upload() {
	if (mcpUniform->Get() != mValue) {
		mcpUniform->Set(mValue);
		mcpUniform->Upload();
	}
}

void UniformTexture2DHolder::Set(Texture2D* pValue) {
	mpValue = pValue;
}

void UniformTexture2DHolder::Upload() {
	if (mcpUniform->Get() != mpValue) {
		mcpUniform->Set(mpValue);
		mcpUniform->Upload();
	}
}