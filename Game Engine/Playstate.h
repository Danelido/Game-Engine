#pragma once
#include "State.h"
#include <vector>
#include "virtualrenderer2d.h"
#include "simple_2d_renderer.h"
#include "static_sprite.h"

#include "batch_renderer.h"
#include "sprite.h"

class Application;


namespace GameState
{

	class Playstate : public State
	{

		public: 
			Playstate(Application& application);
			
			void keyboardInput(sf::Keyboard& keyCode)	override;
			void mouseInput(sf::Mouse& keyCode)			override;
			void update(float delta)					override;
			void draw()									override;
			void cleanup()								override;

		private:
			// Ironic that this renders 3D stuff... 
			// Temporary renderer because it's a inefficent renderer
			Graphics::Simple2DRenderer renderer;

			// matrices
			glm::mat4 projection;
			glm::mat4 model;
			glm::mat4 view;
			
			
			std::vector<Graphics::StaticSprite*> sprites;

			// Position for our nice light
			glm::vec3 lightPosition;

			// Camera
			GLfloat		cameraSpeed		 = 5.0f;									// Camera speed (movement speed)
			GLfloat		yaw				 = -90.f;									// Limit the camera so you cant turn your head upwards 360*
			GLfloat		pitch			 = 0.0f;									// Limit the camera so you cant turn your head upwards 360*
			glm::vec3	cameraPos		 = glm::vec3(520.0f, 50.0f, 520.0f);				// Starting pos for camera
			glm::vec3	cameraFront		 = glm::vec3(0.0f, 0.0f, -1.0f);			// Determine what is front for the camera
			glm::vec3	cameraUp		 = glm::vec3(0.0f, 1.0f, 0.0f);				// Determine what is up for the camera
			glm::vec3	front;
			
			Graphics::BatchRenderer batch;
			std::vector<Graphics::Sprite*> batchsprites;
			


		private:
			void addModel		(Graphics::StaticSprite* sprite);
			void removeModel	(Graphics::StaticSprite& sprite); // Aint working
			void rotateCamera	(glm::vec2 deltaPos);
			void moveCamera		(GLfloat WS_multiplyer, GLfloat AD_mutliplyer);
			void loadModels		();

		private:
			bool RemovingObject = false;
			float RenderDistance = 500;
			sf::Clock clock;
	};

}