#pragma once

#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "Resourcemanager.h"
#include <glm\glm.hpp>

namespace Graphics 
{

	class Model
	{
		
	protected:
		glm::vec3		m_Position;
		glm::vec3		m_Size;
		glm::vec4		m_Color;

		glm::mat4&		m_Model;
		glm::mat4&		m_Projection;
		glm::mat4&		m_View;
		
		bool			m_affectedByLight;
		GLchar*			m_identifier;

	public:
		Model(glm::vec3 position, glm::vec3 size, glm::vec4 color, glm::mat4& model, glm::mat4& projection, glm::mat4& view, bool affectedByLight = true, GLchar* identifier = "cube") :
			m_Position(position), m_Size(size), m_Color(color), m_Model(model),
			m_Projection(projection), m_View(view)
		{}


		virtual ~Model()
		{}



		// Getters
		inline  glm::mat4& getModelMatrix()			{ return m_Model; }
		inline  glm::mat4& getProjectionMatrix()	{ return m_Projection; }
		inline  glm::mat4& getViewMatrix()			{ return m_View; }
		inline  glm::vec3& getSize()				{ return m_Size; }
		inline  glm::vec3& getPosition()			{ return m_Position; }
		inline  glm::vec4& getColor()				{ return m_Color; }
		inline  GLchar* getIdentifier()				{ return m_identifier; }
		// Setters
		void	setPosition(glm::vec3 position)		{ this->m_Position = position; }


	};


}