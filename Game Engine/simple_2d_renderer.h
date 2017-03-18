#pragma once
#include <deque>
#include "virtualrenderer2d.h"
#include "static_sprite.h"

namespace Graphics
{
	class Simple2DRenderer : public VirtualRenderer2D
	{
	private:

		std::deque<StaticSprite*> m_RenderQueue;

	public:

		void submit	(Model* model) override;
		void flush	()			   override;
	};

}