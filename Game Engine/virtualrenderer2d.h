#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "model.h"
namespace Graphics
{
	class VirtualRenderer2D
	{
	public:

		virtual void submit	(Model* renderable) = 0;
		virtual void flush	()					= 0;
	};
}