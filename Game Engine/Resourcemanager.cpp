#include "Resourcemanager.h"
#include <iostream>
namespace Utils {
	
	std::map<std::string, Graphics::Shader> ResourceManager::shaders; // Initialize static variable
	
	void ResourceManager::loadShader(const char * vertexPath, const char * fragmentPath, std::string shaderIdentifier )
	{
		
		Graphics::Shader shader;
		shader.compile(vertexPath, fragmentPath);
		
		shaders[shaderIdentifier] = shader;
		
	}

	Graphics::Shader& ResourceManager::getShader(std::string shaderIdentifier)
	{
		return shaders[shaderIdentifier];
	}


}