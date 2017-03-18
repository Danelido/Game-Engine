#include "buffer.h"

namespace Graphics
{

	Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount)
		: m_componentCount(componentCount)
	{

		glGenBuffers(1, &m_bufferID);												  // Generate a buffer and bind it to an ID
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);									  // Bind the buffer
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW); // Tell OpenGL everything about our data
		glBindBuffer(GL_ARRAY_BUFFER, 0);											  // Unbind it

	}


	void Buffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	}

	void Buffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_bufferID);

	}
}