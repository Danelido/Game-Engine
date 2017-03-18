#pragma once

#include <stack>
#include <memory>
#include "State.h"

class Application
{
	public:
		Application();
		~Application();
		void runGameLoop();
		void pushState(std::unique_ptr<GameState::State> state);
		void popState();

	public:
		const int			getDisplayWidth();
		const int			getDisplayHeight();
		const float			getDisplayRatio();
		sf::RenderWindow&	mainWindow();
		sf::Event&			windowEvent();
		

	private:
		std::stack<std::unique_ptr<GameState::State>> m_states;
		

	
};

