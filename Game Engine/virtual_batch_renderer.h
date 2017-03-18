#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "batchmodel.h"
namespace Graphics
{
	class VirtualBatchRenderer
	{
	public:

		virtual void submit(BatchModel* model) = 0;
		virtual void flush() = 0;
	};
}