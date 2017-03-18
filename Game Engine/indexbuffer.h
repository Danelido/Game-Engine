#pragma once
#include <GL\glew.h>


namespace Graphics
{
	class IndexBuffer
	{

		private:
			GLuint m_bufferID;
			GLuint m_count;

		public:
			IndexBuffer(GLushort* data, GLsizei count);
			IndexBuffer::IndexBuffer(GLuint * data, GLsizei count);
			~IndexBuffer();
			void bind();
			void unbind();

			inline GLuint getCount() { return m_count; };
	};
}