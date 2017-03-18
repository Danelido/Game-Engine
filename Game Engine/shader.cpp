#include "shader.h"
#include <vector>
#include <iostream>

namespace Graphics
{

	Shader& Shader::use()
	{
		glUseProgram(this->m_ShaderID);
		return *this;
	}

	
	void Shader::compile(const char* vertexPath, const char* fragmentPath)
	{
		
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = Utils::FileUtils::read_file(vertexPath);
		std::string fragSourceString = Utils::FileUtils::read_file(fragmentPath);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();


		/*COMPILE VERTEX SHADER*/
		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		/*VERTEX SHADER ERROR CHECKING*/
		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(vertex);

		}

		/*COMPILE FRAGMENT SHADER*/
		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		/*FRAGMENT SHADER ERROR CHECKING*/
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(fragment);

		}

		this->m_ShaderID = glCreateProgram();
		/* If everything went fine attach the shaders, link the shaders and validate the shaders */
		glAttachShader(this->m_ShaderID, vertex);
		glAttachShader(this->m_ShaderID, fragment);

		glLinkProgram(this->m_ShaderID);
		glValidateProgram(this->m_ShaderID);

		/* Delete shaders */
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		
		
	}

	
	/* UNIFORMS */

	/* Location */
	GLint Shader::getUniformLocation(const char* name)
	{
		return glGetUniformLocation(this->m_ShaderID, name);
	}

	/* FLOATS */
	void Shader::setUniform1f(const char* name, float value)
	{
		this->use();
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const char* name, glm::vec2 value)
	{
		this->use();
		glUniform2f(getUniformLocation(name), value.x, value.y);
	}

	void Shader::setUniform3f(const char* name, glm::vec3 value)
	{
		this->use();
		glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::setUniform4f(const char* name, glm::vec4 value)
	{
		this->use();
		glUniform4f(glGetUniformLocation(this->m_ShaderID, name), value.x, value.y, value.z, value.w);
	}

	/* INTEGERS */
	void Shader::setUniform1i(const char* name, int value)
	{
		this->use();
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform2i(const char* name, glm::ivec2 value)
	{
		this->use();
		glUniform2i(getUniformLocation(name), value.x, value.y);
	}

	void Shader::setUniform3i(const char* name, glm::ivec3 value)
	{
		this->use();
		glUniform3i(getUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::setUniform4i(const char* name, glm::ivec4 value)
	{
		this->use();
		glUniform4i(getUniformLocation(name), value.x, value.y, value.z, value.w);
	}


	/* MATRIX */
	void  Shader::setUniformMat4(const char* name, const glm::mat4& matrix)
	{
		this->use();
		glUniformMatrix4fv(glGetUniformLocation(this->m_ShaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	Shader::~Shader()
	{}
	
}