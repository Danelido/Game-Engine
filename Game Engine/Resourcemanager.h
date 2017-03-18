#pragma once
#include <map>
#include <string>
#include "shader.h"


namespace Utils
{

	class ResourceManager
	{

	public:
		static std::map<std::string,Graphics::Shader> shaders;

		static void					loadShader	(const char* vertexPath, const char* fragmentPath, std::string shaderIdentifier);
		static Graphics::Shader&	getShader	(std::string shaderIdentifier);

	private:
		ResourceManager();

	};

}