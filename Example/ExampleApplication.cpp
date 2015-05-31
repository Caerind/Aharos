#include "ExampleApplication.hpp"

ExampleApplication::ExampleApplication() : Application()
{
    FileLogger::openLog("Assets/test.log");
    FileLogger::useConsole(true);
    FileLogger::setTimeFormat("[%x][%X]");

    Window::create(sf::VideoMode(800,600),"Aharos Example");
    Window::setMouseCursorTexture("Assets/cursor.png");
    Window::useCustomMouseCursor();
    Window::setIcon("Assets/icon.png");

    DebugScreen::setFont(ResourceHolder::getFont("Assets/aniron.ttf"));
    DebugScreen::setCharsize(20);
    DebugScreen::showDebugScreen();



    Application::registerState<ExampleState>(ExampleState::getID());
    Application::pushState(ExampleState::getID());
}
