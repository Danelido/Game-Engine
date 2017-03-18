#pragma once
#include <SFML/Graphics.hpp>
class Application;

namespace GameState
{
		class State
		{

			public:
				State(Application& application);
				
				virtual void keyboardInput	(sf::Keyboard& keyCode)	= 0;
				virtual void mouseInput		(sf::Mouse& keyCode)	= 0;
				virtual void update			(float delta)			= 0;
				virtual void draw			()						= 0;
				virtual void cleanup        ()						= 0;

			protected:
				Application* m_application;

		};
}