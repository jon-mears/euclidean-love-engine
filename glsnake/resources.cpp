//#include "resources.h"
//#include "shader.h"
//#include "model.h"
//#include "gameobject.h"
//
//#include <string>
//#include <map>
//
//Shader* Resources::add_shader(std::string name="") {
//	if (name == "") 
//		name = "shader_" + std::to_string(shaders.size() + 1);
//	
//	if (shaders.count(name))
//		throw "a shader named " + name + " already exists.";
//	
//	shaders[name] = new Shader();
//	return shaders[name];
//}
//
//Model* Resources::add_model(std::string name="") {
//
//	if (name == "")
//		name = "model_" + std::to_string(models.size() + 1);
//
//	if (models.count(name))
//		throw "a model named " + name + " already exists.";
//
//	models[name] = new Model();
//	return models[name];
//}
//
//GameObject* Resources::add_object(std::string name="") {
//	if (name == "")
//		name = "object_" + std::to_string(objects.size() + 1);
//
//	if (objects.count(name))
//		throw "an object named " + name + " already exists";
//	
//	objects[name] = new GameObject();
//	return objects[name];
//}
//
//Shader* Resources::shader(const std::string& name) {
//	return shaders.at(name);
//}
//
//Model* Resources::model(const std::string& name) {
//	return models.at(name);
//}
//
//GameObject* Resources::object(const std::string& name) {
//	return objects.at(name);
//}