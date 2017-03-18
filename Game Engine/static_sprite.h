#pragma once

#include "model.h"

namespace Graphics
{

	class StaticSprite : public Model
	{
		private:
			VertexArray*	m_VertexArray;
			IndexBuffer*	m_IndexBuffer;

			Shader&			m_Shader;

		public:
			StaticSprite(glm::vec3 pos, glm::vec3 size, glm::vec4 color, Shader& shader, glm::mat4& model, glm::mat4& projection, glm::mat4& view);
			~StaticSprite();

			inline  VertexArray* getVAO() { return m_VertexArray; }
			inline  IndexBuffer* getIBO() { return m_IndexBuffer; }
			inline  Shader getShader() { return m_Shader; }
	};


}