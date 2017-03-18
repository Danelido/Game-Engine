#include "Display.h"

#include <memory>
#include <GL/glew.h>
#include <iostream>

#define PRINT_FPS_INFO_TO_CONSOLE 0
#define DISPLAY_FPS_COUNTER 1
#define LOCK_FRAMERATE 0
#define ENABLE_VSYNC 0;



namespace Display
{
	// Constants
	constexpr static int			DISPLAYWIDTH  = 1280;
	constexpr static int			DISPLAYHEIGHT = DISPLAYWIDTH / 16 * 9;
	constexpr static char*			DISPLAYTITLE  = "Game Engine";
	constexpr static unsigned int	FRAMELIMIT    = 60;
	constexpr static unsigned int	FONT_SIZE	  = 24;

	// SFML
	sf::Keyboard		keyboardInput;
	sf::Mouse			mouseInput;
	sf::RenderWindow*	DisplayWindow;
	sf::Event			evnt;
	sf::Clock			clock;
	sf::Clock			updateFPSvaluesClock;
	sf::Font*			fps_font;
	sf::Text*			fps_text;


			void init()
			{

				// Settings
				sf::ContextSettings settings;
				settings.depthBits = 24;
				// OpenGL version 3.3
				settings.majorVersion = 3; 
				settings.minorVersion = 3; 

				// Create the window
				DisplayWindow = new sf::RenderWindow(sf::VideoMode(DISPLAYWIDTH, DISPLAYHEIGHT), DISPLAYTITLE, sf::Style::Close, settings);
				DisplayWindow->setMouseCursorVisible(false);
				// Error checking
				if (DisplayWindow == nullptr)
				{
					std::cout << "Error initializing SFML Window!" << std::endl;
				}			
				// Initialize and error check
				if (glewInit())
				{
					std::cout << "Error initializing glew!" << std::endl;
				}
				// Set the viewport
				glViewport(0, 0, DISPLAYWIDTH, DISPLAYHEIGHT);
				// Enable openGL depth thingy
				glEnable(GL_DEPTH_TEST);


				#if	LOCK_FRAMERATE
				// Limit the framerate
				DisplayWindow->setFramerateLimit(FRAMELIMIT);
				#endif

				#if ENABLE_VSYNC
				DisplayWindow->setVerticalSyncEnabled(true);
				#endif

				#if DISPLAY_FPS_COUNTER
				prepareFPStext();
				#endif
			}

			void close()
			{
				delete fps_text;
				delete fps_font;
				DisplayWindow->close();	
			}

			void clear()
			{
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			void update()
			{
				#if DISPLAY_FPS_COUNTER
				updateFramerate();
				#endif
				DisplayWindow->display();
				checkForClose();
			}

			void prepareFPStext()
			{
				 fps_font = new sf::Font();

				if (!fps_font->loadFromFile("Fonts/arial.ttf"))
				{
					printf("Error loading SFML-FONT");
					
				}
			
				fps_text = new sf::Text();
					fps_text->setFont(*fps_font);
					fps_text->setCharacterSize(FONT_SIZE);
					fps_text->setFillColor(sf::Color::Yellow);		
			}

			void updateFramerate() 
			{

				sf::Time time = clock.getElapsedTime();
				#if PRINT_FPS_INFO_TO_CONSOLE				
				printf("fps%4.f\n", 1.0f / time.asSeconds());
				#endif			
				if (updateFPSvaluesClock.getElapsedTime().asSeconds() > 1.0f)
				{
					updateFPSvaluesClock.restart();
					fps_text->setString(std::to_string((int)(1.0f / time.asSeconds())));
				}
				

				clock.restart().asSeconds();
			}

			void checkForClose()
			{	
				while (DisplayWindow->pollEvent(evnt))
				{
					if (evnt.type == sf::Event::Closed)
					{
						close();
						
					}
					if (keyboardInput.isKeyPressed(keyboardInput.Escape))
					{
						close();
					
					}
				}
			}

			bool isOpen()
			{
				return DisplayWindow->isOpen();
			}
			
			sf::Keyboard		getKeyboardEvent()	{ return keyboardInput; }
			sf::Mouse			getMouseEvent()		{ return mouseInput; }
			sf::RenderWindow&   getCurrentWindow()  { return *DisplayWindow; }
			sf::Event&			getWindowEvent()	{ return evnt; }
			sf::Text&			getCurrentFps()		{ return *fps_text; }
			const int			getDisplayWidth()	{ return DISPLAYWIDTH; }
			const int			getDisplayHeight()  { return DISPLAYHEIGHT; }
			
}


