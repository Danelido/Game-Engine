#include "Playstate.h"
#include <iostream>
#include "Resourcemanager.h"
#include "Application.h"
#include "randomizer.h"

namespace GameState
{
// Temporary disable/enable some stuff
#define RENDER_OPTIMIZATiION 0 // Circular
#define RENDER_OPTIMIZATION_RECTANGULAR 1
#define NO_RENDER_OPTIMIZATION 0

// Just in case favor circular
#if NO_RENDER_OPTIMIZATION
#define RENDER_OPTIMIZATiION 0 
#define RENDER_OPTIMIZATION_RECTANGULAR 0
#else
#if RENDER_OPTIMIZATiION
#define RENDER_OPTIMIZATION_RECTANGULAR 0
#endif
#endif

		

		Playstate::Playstate(Application & application)
			: State(application) 
		{
			
			//projection = glm::ortho(0.0f, (GLfloat)m_application->getDisplayWidth(), (GLfloat)m_application->getDisplayHeight(), 0.f, -1.0f, 1.0f);
			projection = glm::perspective(45.0f, m_application->getDisplayRatio(), 0.1f, 1500.0f);
			model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -200.0f));		
			
			// Loading shaders into memory
			Utils::ResourceManager::loadShader("Shaders/basic_vert.glsl", "Shaders/basic_frag.glsl", "basic");
			
			lightPosition = glm::vec3(50.0f, 50.0f, 0.0f);
	
			loadModels();
			
	
		}
		//float dt = 0.0f;
		//bool changeDir = false;
		
		void Playstate::update(float delta)
		{
			
		
			
			
			//dt += 1.0f/350.0f;
			//lightPosition.x += (15.f * cos(dt));
			//lightPosition.y += (15.f * sin(dt));
			//lightPosition.z += (20.f * sin(dt));
			
		
			
			batchsprites.at(0)->setPosition(lightPosition);
		
			


		}
	
		void Playstate::draw()
		{
			view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
			Utils::ResourceManager::getShader("basic").setUniformMat4("view_matrix", glm::translate(view, glm::vec3(0.0, 0.0, -200.0)));
			// Update light position in lightsource and in the basic shader
			Utils::ResourceManager::getShader("basic").use().setUniform3f("light_pos", lightPosition);
			batch.begin();

#if RENDER_OPTIMIZATiION			

			for (size_t i = 0; i < batchsprites.size(); i++)
			{
				glm::vec3 distance = cameraPos - (batchsprites.at(i)->getPosition() + (batchsprites.at(i)->getSize() / 2.0f));
				if (RenderDistance >= sqrt(powf(distance.x, 2) + powf(distance.y, 2) + powf(distance.z, 2)))
				{
					batch.submit(batchsprites.at(i));
				}

				//if ((distance.x <= RenderDistance && distance.y <= RenderDistance && distance.z <= RenderDistance)
				//	&& (distance.x >= -RenderDistance && distance.y >= -RenderDistance && distance.z >= -RenderDistance)) {

			//	}
			}
#endif
#if RENDER_OPTIMIZATION_RECTANGULAR		
			
			for (size_t i = 0; i < batchsprites.size(); i++)
			{
				glm::vec3 distance = cameraPos - (batchsprites.at(i)->getPosition() + (batchsprites.at(i)->getSize() / 2.0f));
				if ((distance.x <= RenderDistance && distance.y <= RenderDistance && distance.z <= RenderDistance)
					&& (distance.x >= -RenderDistance && distance.y >= -RenderDistance && distance.z >= -RenderDistance))
				{
				

						batch.submit(batchsprites.at(i));

				
				}
				
		}
			

#endif
#if NO_RENDER_OPTIMIZATION
			for (size_t i = 0; i < batchsprites.size(); i++)
			{
				batch.submit(batchsprites.at(i));
			}


#endif
				

			batch.end();

			batch.flush();
		
		
		}
		bool singlePress = false;
		void Playstate::keyboardInput(sf::Keyboard& keyCode)
		{
			// Regular keys
			{
				if (keyCode.isKeyPressed(keyCode.W))
				{
					moveCamera(1.0f, 0.0f);
				}

				if (keyCode.isKeyPressed(keyCode.A))
				{
					moveCamera(0.0f, -1.0f);
				}

				if (keyCode.isKeyPressed(keyCode.S))
				{
					moveCamera(-1.0f, 0.0f);
				}

				if (keyCode.isKeyPressed(keyCode.D))
				{
					moveCamera(0.0f, 1.0f);
				}

				if (keyCode.isKeyPressed(keyCode.Space))
				{
					cameraPos += glm::vec3(0.0f, 1.0f, 0.0f);
				}

				if (keyCode.isKeyPressed(keyCode.LControl))
				{
					cameraPos += glm::vec3(0.0f, -1.0f, 0.0f);
				}
			}

			// This is temporary, just for testing lights
			{
				// Arrow keys
				if (keyCode.isKeyPressed(keyCode.Up))
				{
					
					lightPosition += (cameraSpeed * glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw))));
				}
				if (keyCode.isKeyPressed(keyCode.Left))
				{
					lightPosition -= ((glm::cross(glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw))), cameraUp)) * cameraSpeed);
				}
				if (keyCode.isKeyPressed(keyCode.Down))
				{
					lightPosition -= (cameraSpeed * glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw))));
				}
				if (keyCode.isKeyPressed(keyCode.Right))
				{
					lightPosition += ((glm::cross(glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw))), cameraUp)) * cameraSpeed);
				}
				if (keyCode.isKeyPressed(keyCode.G))
				{
					
				}
				if (!keyCode.isKeyPressed(keyCode.G))
				{
					if (singlePress) {
						singlePress = false;
						
					}

				}



			}
		}
		
		void Playstate::mouseInput(sf::Mouse& mouseCode)
		{
			if (m_application->windowEvent().type == sf::Event::MouseMoved) 
			{
				static glm::vec2 lastMousePos;
				glm::vec2 mousePos(m_application->windowEvent().mouseMove.x, m_application->windowEvent().mouseMove.y);

				glm::vec2 deltaPos(mousePos - lastMousePos);
				
				const GLfloat mouseSensitivity = 0.1f;
				deltaPos *= mouseSensitivity;
				deltaPos.y *= -1; // otherwise we get inverse y directions
				
				rotateCamera(deltaPos);

				uint32_t maxMousePosRadius = glm::min(m_application->getDisplayWidth(), m_application->getDisplayHeight()) / 3;
				glm::vec2 windowCenter(m_application->getDisplayWidth() / 2, m_application->getDisplayHeight() / 2);

				if (glm::length(mousePos - windowCenter) > maxMousePosRadius)
				{

					mouseCode.setPosition(sf::Vector2i((int)windowCenter.x, (int)windowCenter.y), m_application->mainWindow());
					lastMousePos = windowCenter;

				}
				else {
					lastMousePos = mousePos;
				}


			}

			
		}

		void Playstate::rotateCamera(glm::vec2 deltaPos)
		{
			yaw   += deltaPos.x;
			pitch += deltaPos.y;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;


			front.x		= cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y		= sin(glm::radians(pitch));
			front.z		= sin(glm::radians(yaw)) * cos(glm::radians(pitch));

			cameraFront = glm::normalize(front);
		}

		void Playstate::moveCamera(GLfloat WS_multiplyer, GLfloat AD_mutliplyer)
		{
			
			cameraPos += WS_multiplyer * (cameraSpeed * glm::vec3(cos(glm::radians(yaw)),  0.0f,   sin(glm::radians(yaw))));
			cameraPos += AD_mutliplyer * ( (glm::cross(glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw))), cameraUp)) * cameraSpeed );
		}

		void Playstate::loadModels()
		{
			
			// Activate "basic" shader and send in some variables
			Utils::ResourceManager::getShader("basic").use();
			Utils::ResourceManager::getShader("basic").setUniformMat4("model_matrix", glm::translate(model, glm::vec3(1, 1, 1)));
			Utils::ResourceManager::getShader("basic").setUniformMat4("projection_matrix", projection);
				

				batchsprites.push_back(
					new Graphics::Sprite(
					lightPosition,
					glm::vec3(5.f, 5.f, 5.f),
					glm::vec4(0.2f, 0.9f, 0.5f, 1.0)));


				int min = -20;
				int max = 20;

	
				for (int x = 0; x < 5; x++)
				{
					for (int z = 0; z < 5; z++) {

						for (int y = 0; y < 5; y++) {

							batchsprites.push_back(
								new Graphics::Sprite(
									glm::vec3( (float)Utils::getRandomNumber(min, max) *x, (float)Utils::getRandomNumber(min, max) * y, (float)Utils::getRandomNumber(min, max) * z),
									glm::vec3(5.f, 5.f, 5.f),
									glm::vec4(abs(cos(y)), (128.0f / 255.0f), (144.0f / 255.0f), 1.0)));

						}
					
					
					}
				}
				

				batchsprites.push_back(
					new Graphics::Sprite(
						glm::vec3(535.0f, 0.0f, 535.0f),
						glm::vec3(50.f, 50.f, 50.f),
						glm::vec4((.0f), (102.f / 255.0f), (102.0f / 255.0f), 1.0)));

				

		}

		void Playstate::addModel(Graphics::StaticSprite* sprite)
		{
			sprites.push_back(sprite);
		}

		void Playstate::removeModel(Graphics::StaticSprite& sprite)
		{
		
		}

		void Playstate::cleanup()
		{
			for (size_t i = 0; i < sprites.size(); i++)
			{
				delete sprites.at(i);
			}
			for (size_t i = 0; i < batchsprites.size(); i++)
			{
				delete batchsprites.at(i);
			}
			
		}
}