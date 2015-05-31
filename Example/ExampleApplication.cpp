#include "ExampleApplication.hpp"

ExampleApplication::ExampleApplication() : ah::Application()
{
    ah::Log::openLog("Example/test.log");
    ah::Log::useConsole(true);
    ah::Log::setTimeFormat("[%x][%X]");

    ah::Lang::loadLang("Example/fr.txt");

    ah::Window::create(sf::VideoMode(800,600),ah::Lang::getLang("window-title"));
    ah::Window::setMouseCursorTexture("Example/cursor.png");
    ah::Window::useCustomMouseCursor();
    ah::Window::setIcon("Example/icon.png");

    ah::DebugScreen::setFont(ah::ResourceHolder::getFont("Example/aniron.ttf"));
    ah::DebugScreen::setCharsize(20);
    ah::DebugScreen::showDebugScreen();

    ah::DataManager::setData("sound-name","Example/explosion.wav");
    ah::DataManager::setData<float>("speed-x",75.f);

    ah::Application::registerState<ExampleState>(ExampleState::getID());
    ah::Application::pushState(ExampleState::getID());
}
