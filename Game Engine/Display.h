#pragma once
#include <SFML/Graphics.hpp>

namespace Display
{
		// Initialize 
		void init();
		// Handle closing
		void close();
		// Clear everything
		void clear();
		// Update
		void update();
		// Check if window being closed
		void checkForClose();
		// Return true if window is open
		bool isOpen();
		// Prepare fps text to be renderer to the screen
		void prepareFPStext();
		// Display window fps
		void updateFramerate();
		// Return the main event
		sf::Event& getWindowEvent();
		// Return SFML Keyboard event for keyboard handling
		sf::Keyboard getKeyboardEvent();
		// Return SFML Mouse event for mouse handling
		sf::Mouse getMouseEvent();
		// Return SFML winodw
		sf::RenderWindow& getCurrentWindow();
		// Return the current fps
		sf::Text& getCurrentFps();
		// Return Window Width
		const int getDisplayWidth();
		// Return Window Height
		const int getDisplayHeight();
}