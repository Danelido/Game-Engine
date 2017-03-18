#pragma once
#include <glm\glm.hpp>

namespace Graphics
{

	struct VertexData
	{
		glm::vec3 vertex;
		glm::vec3 normals;
		
		unsigned int colors;
		

	};

	class BatchModel
	{

	protected:
		glm::vec3		m_Position;
		glm::vec3		m_Size;
		glm::vec4		m_Color;


	

	

	public:
		BatchModel(glm::vec3 position, glm::vec3 size, glm::vec4 color) :
			m_Position(position), m_Size(size), m_Color(color)
		{
			
		}


		virtual ~BatchModel()
		{
			
		}



		// Getters
		inline  glm::vec3& getSize() { return m_Size; }
		inline  glm::vec3& getPosition() { return m_Position; }
		inline  glm::vec4& getColor() { return m_Color; }
		// Setters
		void	setPosition(glm::vec3 position) { this->m_Position = position; }


	};


}