#include "../Source/Application.hpp"

#include "ExampleState.hpp"

int main()
{
    // Load DebugScreen
    ah::Application::instance().loadFont("aniron","aniron.ttf");
    ah::Application::instance().setFont(ah::Application::instance().getFont("aniron"));
    ah::Application::instance().showDebugScreen(true);
	
	// Load Log
	ah::Application::instance().openLog("test.txt");
    ah::Application::instance().useConsole(true);
	ah::Application::instance().log("Log System");

    // Load Window
    ah::Application::instance().create(sf::VideoMode(800,600),"Aharos Example");
    ah::Application::instance().setIcon("icon.png");
    ah::Application::instance().setMouseCursorTexture("cursor.png");
    ah::Application::instance().useCustomMouseCursor();

    // Register States
    ah::Application::instance().registerState<ExampleState>(ExampleState::getID());
	
    // Run Application
    ah::Application::instance().pushState(ExampleState::getID());
    ah::Application::instance().run();

    return EXIT_SUCCESS;
}
