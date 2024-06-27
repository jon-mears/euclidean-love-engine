#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>
#include <map>

#include "shader.h"
#include "gameobject.h"
#include "mesh.h"

class Resource;
class GameObject;
class XMLNode;
class XMLTree;
class Shader;
class Mesh;

class ResourceManager {
private:
	std::map<std::string, Resource*> mResources;
	std::map<std::string, Shader*> mShaders;
	std::map<std::string, GameObject*> mGameObjects;
	std::map<std::string, Mesh*> mMeshes;

	ResourceManager();
	ResourceManager(ResourceManager &lhs) = delete;
	ResourceManager& operator=(ResourceManager& lhs) = delete;
	ResourceManager& operator=(ResourceManager lhs) = delete;

	void startup();

	class XMLResourceTreeParser {
	private:
		Shader* parse_shader(XMLNode* pNode);
	public:
		void parse_tree(XMLTree* tree, ResourceManager& rm);
	} mXmlTreeParser;

public:
	template <typename T>
	T* retrieve(const std::string name) = delete; // only allow specializations

	template <>
	Shader* retrieve<Shader>(const std::string name) {
		return mShaders[name];
	}

	template <>
	GameObject* retrieve<GameObject>(const std::string name) {
		return mGameObjects[name];
	}

	template <>
	Mesh* retrieve<Mesh>(const std::string name) {
		return mMeshes[name];
	}

	template <typename T>
	void add(T* r) = delete; // only allow specializations

	template <>
	void add<Shader>(Shader* s) {
		mShaders[s->name()] = s;
		mResources[s->name()] = s;
	}

	template <>
	void add<GameObject>(GameObject* go) {
		mGameObjects[go->name()] = go;
		mResources[go->name()] = go;
	}

	template <>
	void add<Mesh>(Mesh* m) {
		mMeshes[m->name()] = m;
		mResources[m->name()] = m;
	}

	template <typename T>
	typename std::map<std::string, T*>::iterator begin() = delete; // only allow specializations

	template <>
	typename std::map<std::string, Shader*>::iterator begin<Shader>() {
		return mShaders.begin();
	}

	template <>
	typename std::map<std::string, GameObject*>::iterator begin<GameObject>() {
		return mGameObjects.begin();
	}

	template <>
	typename std::map<std::string, Mesh*>::iterator begin<Mesh>() {
		return mMeshes.begin();
	}

	template <typename T>
	typename std::map<std::string, T*>::iterator end() = delete; // only allow specializations

	template <>
	typename std::map<std::string, Shader*>::iterator end<Shader>() {
		return mShaders.end();
	}

	template <>
	typename std::map<std::string, GameObject*>::iterator end<GameObject>() {
		return mGameObjects.end();
	}

	template <>
	typename std::map<std::string, Mesh*>::iterator end<Mesh>() {
		return mMeshes.end();
	}

	static ResourceManager& instance();

	friend class Game;
};
#endif