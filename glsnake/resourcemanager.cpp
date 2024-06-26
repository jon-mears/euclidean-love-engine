#include "resourcemanager.hpp"
#include "resource.hpp"
#include "xmlparser.hpp"
#include "xmltree.hpp"
#include "xmlnode.hpp"
#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

ResourceManager::ResourceManager() : mXmlTreeParser() { }

void ResourceManager::startup() {
	XMLParser* pParser = new XMLParser();
	XMLTree* pTree = pParser->parse("C:\\assets\\resources.xml");

	mXmlTreeParser.parse_tree(pTree, *this);
}

void ResourceManager::add_resource(Resource* pResource) {

	if (mResources.count(pResource->name())) {
		std::cout << "a resource named " << pResource->name() << " already exists!" << std::endl;
	}

	else {
		mResources[pResource->name()] = pResource;
	}
}

void ResourceManager::XMLResourceTreeParser::parse_tree(XMLTree* pTree, ResourceManager& rm) {
	for (size_t i = 0; i < pTree->root()->num_children(); ++i) {
		XMLNode* pNode = pTree->root()->child(i);

		const std::string tagname = pNode->tag();

		if (tagname == "shader") {
			rm.add_resource(parse_shader(pNode));
		}

	}
}

Shader *ResourceManager::XMLResourceTreeParser::parse_shader(XMLNode* pNode) {
	Shader* pShader = new Shader(pNode->attribute("name"));

	for (size_t i = 0; i < pNode->num_children(); ++i) {
		XMLNode* pChild = pNode->child(i);

		if (pChild->tag() == "vertex") {
			const std::string filename = pChild->content();

			std::ifstream vsourcefile("C:\\assets\\" + filename);
			if (!vsourcefile.is_open()) {
				std::cout << "could not open " << filename << "!" << std::endl;
				std::exit(-1);
			}

			std::stringstream buffer;
			buffer << vsourcefile.rdbuf();

			pShader->vertex(buffer.str());
		}

		else if (pChild->tag() == "fragment") {
			const std::string filename = pChild->content();

			std::ifstream fsourcefile("C:\\assets\\" + filename);
			if (!fsourcefile.is_open()) {
				std::cout << "could not open " << filename << "!" << std::endl;
				std::exit(-1);
			}

			std::stringstream buffer;
			buffer << fsourcefile.rdbuf();

			pShader->fragment(buffer.str());
		}
	}

	pShader->compile();
	return pShader;
}