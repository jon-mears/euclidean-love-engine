#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#define RETRIEVE_SPECIALIZATION(classname, containername)	\
template <> \
classname* Retrieve<classname>(const std::string& name) { \
	return containername.at(name); \
}

#define BEGIN_SPECIALIZATION(classname, containername)	\
template <> \
typename std::map<std::string, classname*>::iterator Begin<classname>() { \
	return containername.begin();\
}

#define END_SPECIALIZATION(classname, containername)	\
template <> \
typename std::map<std::string, classname*>::iterator End<classname>() { \
	return containername.end();\
}

#define NEW_SPECIALIZATION(classname, containername)	\
template <>	\
classname* New<classname>(const std::string& name) { \
	classname* pResource = new classname(); \
	containername[name] = pResource; \
	return pResource; \
}

#define ADD_SPECIALIZATION(classname, containername)	\
template <> \
void Add<classname>(classname* pResource, const std::string& name) { \
	containername[name] = pResource; \
}

#include <map>
#include <string>
#include <map>

#include "shader.hpp"
#include "game-object.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "framebuffer.hpp"
#include "renderbuffer.hpp"
#include "image.hpp"

class Resource;
class GameObject;
class XMLNode;
class XMLTree;
class Shader;
class Mesh;
class Texture1D;
class Texture2D;
class Texture3D;
class Image1D;
class Image2D;
class Image3D;
class Framebuffer;
class Renderbuffer;

class ResourceManager {
private:
	std::map<std::string, Resource*> mResources;
	std::map<std::string, Shader*> mShaders;
	std::map<std::string, GameObject*> mGameObjects;
	std::map<std::string, Mesh*> mMeshes;
	std::map<std::string, Texture1D*> mTexture1Ds;
	std::map<std::string, Texture2D*> mTexture2Ds;
	std::map<std::string, Texture3D*> mTexture3Ds;
	std::map<std::string, Image1D*> mImage1Ds;
	std::map<std::string, Image2D*> mImage2Ds;
	std::map<std::string, Image3D*> mImage3Ds;
	std::map<std::string, Framebuffer*> mFramebuffers;
	std::map<std::string, Renderbuffer*> mRenderbuffers;

	ResourceManager();
	ResourceManager(ResourceManager &lhs) = delete;
	ResourceManager& operator=(ResourceManager& lhs) = delete;
	ResourceManager& operator=(ResourceManager lhs) = delete;

	void Startup();

	class XMLResourceTreeParser {
	private:
		void ParseShader(XMLNode* pNode);
		void ParseTexture2D(XMLNode* pNode);
	public:
		void ParseTree(XMLTree* pTree);
	} mXmlTreeParser;

public:
	template <typename T>
	T* Retrieve(const std::string& name) = delete; // only allow specializations

	RETRIEVE_SPECIALIZATION(Shader, mShaders)
	RETRIEVE_SPECIALIZATION(GameObject, mGameObjects)
	RETRIEVE_SPECIALIZATION(Mesh, mMeshes)
	RETRIEVE_SPECIALIZATION(Texture1D, mTexture1Ds)
	RETRIEVE_SPECIALIZATION(Texture2D, mTexture2Ds)
	RETRIEVE_SPECIALIZATION(Texture3D, mTexture3Ds)
	RETRIEVE_SPECIALIZATION(Image1D, mImage1Ds)
	RETRIEVE_SPECIALIZATION(Image2D, mImage2Ds)
	RETRIEVE_SPECIALIZATION(Image3D, mImage3Ds)
	RETRIEVE_SPECIALIZATION(Framebuffer, mFramebuffers)
	RETRIEVE_SPECIALIZATION(Renderbuffer, mRenderbuffers)

	template <typename T>
	typename std::map<std::string, T*>::iterator Begin() = delete; // only allow specializations

	BEGIN_SPECIALIZATION(Shader, mShaders)
	BEGIN_SPECIALIZATION(GameObject, mGameObjects)
	BEGIN_SPECIALIZATION(Mesh, mMeshes)
	BEGIN_SPECIALIZATION(Texture1D, mTexture1Ds)
	BEGIN_SPECIALIZATION(Texture2D, mTexture2Ds)
	BEGIN_SPECIALIZATION(Texture3D, mTexture3Ds)
	BEGIN_SPECIALIZATION(Image1D, mImage1Ds)
	BEGIN_SPECIALIZATION(Image2D, mImage2Ds)
	BEGIN_SPECIALIZATION(Image3D, mImage3Ds)
	BEGIN_SPECIALIZATION(Framebuffer, mFramebuffers)
	BEGIN_SPECIALIZATION(Renderbuffer, mRenderbuffers)

	template <typename T>
	typename std::map<std::string, T*>::iterator End() = delete; // only allow specializations

	END_SPECIALIZATION(Shader, mShaders)
	END_SPECIALIZATION(GameObject, mGameObjects)
	END_SPECIALIZATION(Mesh, mMeshes)
	END_SPECIALIZATION(Texture1D, mTexture1Ds)
	END_SPECIALIZATION(Texture2D, mTexture2Ds)
	END_SPECIALIZATION(Texture3D, mTexture3Ds)
	END_SPECIALIZATION(Image1D, mImage1Ds)
	END_SPECIALIZATION(Image2D, mImage2Ds)
	END_SPECIALIZATION(Image3D, mImage3Ds)
	END_SPECIALIZATION(Framebuffer, mFramebuffers)
	END_SPECIALIZATION(Renderbuffer, mRenderbuffers)

	template <typename T>
	T* New(const std::string& name="") = delete; // only allow specializations

	NEW_SPECIALIZATION(Shader, mShaders)
	NEW_SPECIALIZATION(GameObject, mGameObjects)
	NEW_SPECIALIZATION(Mesh, mMeshes)
	NEW_SPECIALIZATION(Texture1D, mTexture1Ds)
	NEW_SPECIALIZATION(Texture2D, mTexture2Ds)
	NEW_SPECIALIZATION(Texture3D, mTexture3Ds)
	NEW_SPECIALIZATION(Image1D, mImage1Ds)
	NEW_SPECIALIZATION(Image2D, mImage2Ds)
	NEW_SPECIALIZATION(Image3D, mImage3Ds)
	NEW_SPECIALIZATION(Framebuffer, mFramebuffers)
	NEW_SPECIALIZATION(Renderbuffer, mRenderbuffers)

	template <typename T>
	void Add(T* pItem, const std::string& name = "") = delete; // only allow specializations

	ADD_SPECIALIZATION(Shader, mShaders)
	ADD_SPECIALIZATION(GameObject, mGameObjects)
	ADD_SPECIALIZATION(Mesh, mMeshes)
	ADD_SPECIALIZATION(Texture1D, mTexture1Ds)
	ADD_SPECIALIZATION(Texture2D, mTexture2Ds)
	ADD_SPECIALIZATION(Texture3D, mTexture3Ds)
	ADD_SPECIALIZATION(Image1D, mImage1Ds)
	ADD_SPECIALIZATION(Image2D, mImage2Ds)
	ADD_SPECIALIZATION(Image3D, mImage3Ds)
	ADD_SPECIALIZATION(Framebuffer, mFramebuffers)
	ADD_SPECIALIZATION(Renderbuffer, mRenderbuffers)

	static ResourceManager& Instance();

	friend class App;
};
#endif