#include "resource-manager.hpp"
#include "xml-parser.hpp"
#include "xml-tree.hpp"
#include "xml-node.hpp"
#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

ResourceManager::ResourceManager() : mXmlTreeParser() { }

void ResourceManager::Startup() {
	XMLParser* pParser = new XMLParser();
	XMLTree* pTree = pParser->Parse("C:\\assets\\resources.xml");

	mXmlTreeParser.ParseTree(pTree);
}

void ResourceManager::XMLResourceTreeParser::ParseTree(XMLTree* pTree) {
	for (size_t i = 0; i < pTree->Root()->NumChildren(); ++i) {
		XMLNode* pNode = pTree->Root()->Child(i);

		const std::string tagname = pNode->Tag();

		if (tagname == "Shader") {
			ParseShader(pNode);
		}

		//else if (tagname == "Texture2D") {
		//	ParseTexture2D(pNode);
		//}
	}
}

void ResourceManager::XMLResourceTreeParser::ParseShader(XMLNode* pNode) {
	Shader* pShader = ResourceManager::Instance().New<Shader>(pNode->Attribute("Name"));

	for (size_t i = 0; i < pNode->NumChildren(); ++i) {
		XMLNode* pChild = pNode->Child(i);

		if (pChild->Tag() == "Vertex") {
			const std::string filename = pChild->Content();

			std::ifstream vsourcefile("C:\\assets\\" + filename);
			if (!vsourcefile.is_open()) {
				std::cerr << "could not open " << filename << "!" << std::endl;
				std::exit(-1);
			}

			std::stringstream buffer;
			buffer << vsourcefile.rdbuf();

			pShader->ProvideVertexSource(buffer.str());
		}

		else if (pChild->Tag() == "Fragment") {
			const std::string filename = pChild->Content();

			std::ifstream fsourcefile("C:\\assets\\" + filename);
			if (!fsourcefile.is_open()) {
				std::cerr << "could not open " << filename << "!" << std::endl;
				std::exit(-1);
			}

			std::stringstream buffer;
			buffer << fsourcefile.rdbuf();

			pShader->ProvideFragmentSource(buffer.str());
		}
	}

	pShader->Compile();
}

void ResourceManager::XMLResourceTreeParser::ParseTexture2D
(XMLNode* pNode) {
	Texture2D* pTexture = ResourceManager::Instance().New
		<Texture2D>(pNode->Attribute("Name"));

	for (size_t i = 0; i < pNode->NumChildren(); ++i) {
		XMLNode* pChild = pNode->Child(i);

		if (pChild->Tag() == "Image2D") {
			Image2D* pImage = new Image2D();
			pImage->Open("C:\\assets\\" + pChild->Content());
			pTexture->SetImage(pImage);
		}
	}
}

ResourceManager& ResourceManager::Instance() {
	static ResourceManager gResourceManager;
	return gResourceManager;
}