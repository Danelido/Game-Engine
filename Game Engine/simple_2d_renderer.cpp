#include "simple_2d_renderer.h"
#include <iostream>

namespace Graphics
{

	void Simple2DRenderer::submit(Model* model)
	{
		m_RenderQueue.push_back((StaticSprite*)model);
	
	}

	void Simple2DRenderer::flush()
	{
		while (!m_RenderQueue.empty())
		{

			StaticSprite* sprite = m_RenderQueue.front();
			
			sprite->getVAO()->bind();
			sprite->getIBO()->bind();
	
			sprite->getShader().setUniformMat4("model_matrix", glm::translate(sprite->getModelMatrix(), sprite->getPosition() ));
			sprite->getShader().setUniformMat4("view_matrix", glm::translate(sprite->getViewMatrix(),glm::vec3(0.0,0.0, -200.0)));
			
			glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

			sprite->getIBO()->unbind();
			sprite->getVAO()->unbind();
	
			m_RenderQueue.pop_front();
			
		}

	}

}