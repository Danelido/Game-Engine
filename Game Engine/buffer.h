#pragma once
#include <GL/glew.h>

namespace Graphics
{


	class Buffer
	{

		private:
			GLuint m_bufferID;
			GLuint m_componentCount;

		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();
			void bind();
			void unbind();

			inline GLuint getComponentCount() { return m_componentCount; };

	};



}

