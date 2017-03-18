#pragma once
#include "indexbuffer.h"
#include "vertexarray.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Graphics
{
	

	class TerrainRenderer
	{

		private:
			GLuint m_VAO;
			GLuint m_VBO;
			GLsizei m_indexCount;
			IndexBuffer* m_IBO;


		public:
			TerrainRenderer();
			~TerrainRenderer();

			void init();

			void begin();

			void end();
			
			void flush();


	};



}
