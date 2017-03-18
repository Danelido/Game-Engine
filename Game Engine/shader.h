#pragma once
#include "fileutils.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.inl>
#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{

	class Shader
	{
	private:
		GLuint			m_ShaderID;
		const char*		m_Vertpath;
		const char*		m_Fragpath;


	public:
		Shader(){}
		~Shader();
		
		Shader& use();
		
		void compile(const char* vertexPath, const char* fragmentPath);
		
		void setUniform1f	(const char* name, float value);
		void setUniform2f	(const char* name, glm::vec2 value);
		void setUniform3f	(const char* name, glm::vec3 value);
		void setUniform4f	(const char* name, glm::vec4 value);

		void setUniform1i	(const char* name, int value);
		void setUniform2i	(const char* name, glm::ivec2 value);
		void setUniform3i	(const char* name, glm::ivec3 value);
		void setUniform4i	(const char* name, glm::ivec4 value);

		void setUniformMat4	(const char* name, const glm::mat4& matrix);

	
	private:
		GLint getUniformLocation(const char* name);
	};




}