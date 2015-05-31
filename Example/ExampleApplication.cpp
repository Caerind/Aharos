#include "ExampleApplication.hpp"

ExampleApplication::ExampleApplication() : ah::Application()
{
    ah::FileLogger::openLog("Assets/test.log");
    ah::FileLogger::useConsole(true);
    ah::FileLogger::setTimeFormat("[%x][%X]");

    ah::Window::create(sf::VideoMode(800,600),"Aharos Example");
    ah::Window::setMouseCursorTexture("Assets/cursor.png");
    ah::Window::useCustomMouseCursor();
    ah::Window::setIcon("Assets/icon.png");

    ah::DebugScreen::setFont(ah::ResourceHolder::getFont("Assets/aniron.ttf"));
    ah::DebugScreen::setCharsize(20);
    ah::DebugScreen::showDebugScreen();

    // ...

    ah::Application::registerState<ExampleState>(ExampleState::getID());
    ah::Application::pushState(ExampleState::getID());
}
