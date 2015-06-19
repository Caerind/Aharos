#include "../Source/Application.hpp"
#include "ExampleState.hpp"

int main()
{
    ah::Application::instance().create(sf::VideoMode(800,600),"Example");
    ah::Application::instance().openLog("Example/test.log");
    ah::Application::instance() << "Loaded";
    ah::Application::instance().registerState<ExampleState>(ExampleState::getID());
    ah::Application::instance().setAction("close",thor::Action(sf::Event::Closed));
    ah::Application::instance().bind("close",[&](ah::ActionTarget::Context context){context.window->close();});
    ah::Application::instance().loadTexture("cb","Example/cb.bmp");
    ah::Application::instance().pushState(ExampleState::getID());
    ah::Application::instance().run();
    return EXIT_SUCCESS;
}
