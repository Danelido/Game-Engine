#include "batch_renderer.h"
#include <iostream>
namespace Graphics
{

	BatchRenderer::BatchRenderer()
	{

		init();
	}

	void BatchRenderer::init()
	{

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_NORMALS_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_NORMALS_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::normals));
	    glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::colors));
		
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		static GLuint indices[RENDERER_INDICES_SIZE];
		int offset = 0;

		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 36)
		{
			// First
			indices[i + 0] = (offset + 0);
			indices[i + 1] = (offset + 1);
			indices[i + 2] = (offset + 2);

			indices[i + 3] = (offset + 2);
			indices[i + 4] = (offset + 3);
			indices[i + 5] = (offset + 0);

			offset += 4;

			// Second
			indices[i + 6] = (offset + 0);
			indices[i + 7] = (offset + 1);
			indices[i + 8] = (offset + 2);

			indices[i + 9] = (offset + 2);
			indices[i + 10] = (offset + 3);
			indices[i + 11] = (offset + 0);

			offset += 4;

			// Third
			indices[i + 12] = (offset + 0);
			indices[i + 13] = (offset + 1);
			indices[i + 14] = (offset + 2);

			indices[i + 15] = (offset + 2);
			indices[i + 16] = (offset + 3);
			indices[i + 17] = (offset + 0);

			offset += 4;

			// Fourth
			indices[i + 18] = (offset + 0);
			indices[i + 19] = (offset + 1);
			indices[i + 20] = (offset + 2);

			indices[i + 21] = (offset + 2);
			indices[i + 22] = (offset + 3);
			indices[i + 23] = (offset + 0);

			offset += 4;

			// Fifth
			indices[i + 24] = (offset + 0);
			indices[i + 25] = (offset + 1);
			indices[i + 26] = (offset + 2);

			indices[i + 27] = (offset + 2);
			indices[i + 28] = (offset + 3);
			indices[i + 29] = (offset + 0);

			offset += 4;

			// Sixth
			indices[i + 30] = (offset + 0);
			indices[i + 31] = (offset + 1);
			indices[i + 32] = (offset + 2);

			indices[i + 33] = (offset + 2);
			indices[i + 34] = (offset + 3);
			indices[i + 35] = (offset + 0);

			offset += 4;
			
		}

		m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

		glBindVertexArray(0);



	}

	void BatchRenderer::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer::submit(BatchModel* model)
	{
		
		glm::vec3& size = model->getSize();
		glm::vec3& position = model->getPosition();
		glm::vec4& color = model->getColor();

		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;

		unsigned int c = a << 24 | b << 16 | g << 8 | r;

		// BACK SIDE
		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 0.0f, -1.0f);
		m_Buffer++;

		m_Buffer->vertex = position;
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 0.0f, -1.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 0.0f, -1.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 0.0f, -1.0f);
		m_Buffer++;

		// RIGHT SIDE
		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Buffer++;

		// FRONT SIDE
		m_Buffer->vertex = glm::vec3(position.x, position.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 0.0f, 1.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 0.0f, 1.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 0.0f, 1.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 0.0f, 1.0f);
		m_Buffer++;

		// LEFT SIDE
		m_Buffer->vertex = position;
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(-1.0f, 0.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x, position.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(-1.0f, 0.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(-1.0f, 0.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(-1.0f, 0.0f, 0.0f);
		m_Buffer++;

		// TOP SIDE
		m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Buffer++;

		// BOTTOM SIDE
		m_Buffer->vertex = position;
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, -1.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, -1.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, -1.0f, 0.0f);
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x, position.y, position.z + size.z);
		m_Buffer->colors = c;
		m_Buffer->normals = glm::vec3(0.0f, -1.0f, 0.0f);
		m_Buffer++;


		m_indexCount += 36;
		
	}

	void BatchRenderer::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer::flush()
	{
		glBindVertexArray(m_VAO);
		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

		m_IBO->unbind();
		glBindVertexArray(0);

		m_indexCount = 0;

	}

	BatchRenderer::~BatchRenderer()
	{
		delete m_IBO;
		glDeleteBuffers(1, &m_VBO);
	}

}