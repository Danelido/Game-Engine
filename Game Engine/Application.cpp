#include "Application.h"
#include "Display.h"
#include "Playstate.h"
#include <iostream>

		Application::Application()
		{	
			pushState(std::make_unique<GameState::Playstate>(*this));
		}

		Application::~Application()
		{
			m_states.top()->cleanup();
		}
	
		void Application::runGameLoop()
		{
			sf::Clock clock;
			float dt = 1.0f / 60.f;
			float firstTime = clock.getElapsedTime().asSeconds();
			float accumulator = 0.0f;
			int s = 0;

			while (Display::isOpen())
			{

					Display::clear();	// Clear the display

					// Update
					float currentTime = clock.getElapsedTime().asSeconds();
					float currentFrame = currentTime - firstTime;

					if (currentFrame > 0.25f) {
						currentFrame = 0.25f;
					}

					firstTime = currentTime;
					accumulator += currentFrame;

					while (accumulator >= dt)
					{
						// OpenGL calls
						m_states.top()->keyboardInput(Display::getKeyboardEvent());
						m_states.top()->mouseInput(Display::getMouseEvent());
						m_states.top()->update(dt);
						
						
						accumulator -= dt;
					}
					// could draw with renderdelta
					//const float renderDelta = accumulator / dt;
				
					
					m_states.top()->draw();

					mainWindow().pushGLStates(); // Save the opengl "state" to prepare to render sfml stuff
					mainWindow().draw(Display::getCurrentFps());
					mainWindow().popGLStates(); // switch states again

					
					Display::update();	// Update the display
				

					

					
			}
		}

		void Application::pushState(std::unique_ptr<GameState::State> state)
		{
			m_states.push(std::move(state));
		}

		void Application::popState()
		{
			m_states.pop();
		}

		// Getters
		sf::RenderWindow&	Application::mainWindow()
		{ 
			return Display::getCurrentWindow(); 
		}

		sf::Event&			Application::windowEvent()
		{
			return Display::getWindowEvent();
		}

		const int			Application::getDisplayWidth()
		{
			return Display::getDisplayWidth();
		}

		const int			Application::getDisplayHeight()
		{
			return Display::getDisplayHeight();
		}
		
		const float			Application::getDisplayRatio()
		{
			return ( (float)Display::getDisplayWidth() / (float)Display::getDisplayHeight() );
		}
