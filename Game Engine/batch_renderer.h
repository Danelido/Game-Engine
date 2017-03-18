#pragma once
#include <cstddef>
#include "virtual_batch_renderer.h"
#include "indexbuffer.h"

namespace Graphics
{

	constexpr static int RENDERER_MAX_SPRITES = 10000;
	constexpr static int RENDERER_VERTEX_SIZE = sizeof(VertexData);
	constexpr static int RENDERER_SPRITE_SIZE = RENDERER_VERTEX_SIZE * 24;
	constexpr static int RENDERER_BUFFER_SIZE = RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES;
	constexpr static int RENDERER_INDICES_SIZE = RENDERER_MAX_SPRITES * 36;
	
	constexpr static int SHADER_VERTEX_INDEX = 0;
	constexpr static int SHADER_NORMALS_INDEX = 1;
	constexpr static int SHADER_COLOR_INDEX = 2;

	class BatchRenderer : public VirtualBatchRenderer
	{

		private:
			GLuint m_VAO;
			GLuint m_VBO;
			GLsizei m_indexCount;
			IndexBuffer* m_IBO;
			VertexData* m_Buffer;
			
			
			

		public:
			BatchRenderer();
			~BatchRenderer();
			void begin();
			void submit(BatchModel* model)		override;
			void end();
			void flush()						override;

	

		private:
			void init();

	};


}