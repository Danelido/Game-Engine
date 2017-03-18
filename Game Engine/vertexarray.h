#pragma once
#include <vector>
#include <GL/glew.h>
#include "buffer.h"

namespace Graphics
{
	class VertexArray
	{
		private:
			GLuint m_arrayID;
			std::vector<Buffer*> m_Buffers;

		public:
			VertexArray();
			~VertexArray();

			void addBuffers(Buffer* buffer, GLuint index);

			void bind();
			void unbind();
	};
}
