#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>

class Resource;
class XMLNode;
class XMLTree;
class Shader;

class ResourceManager {
private:
	std::map<std::string, Resource*> mResources;
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
	T* retrieve(const std::string name);

	void add_resource(Resource* r);
	friend class Game;
};

#include "resourcemanager.tpp"
#endif