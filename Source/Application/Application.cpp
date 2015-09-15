#include "Application.hpp"

namespace ah
{

Application Application::mInstance;

Application& Application::instance()
{
    return mInstance;
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	while (isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		bool repaint = false;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			handleEvents();
			update(TimePerFrame);

			if (mStates.empty())
                close();

			std::cout << std::flush;

			repaint = true;
		}

        if (repaint)
            render();
	}
}

void Application::pushState(std::string const& stateId)
{
    mStates.pushState(stateId);
}


Application::Application() : mStates(*this), mFpsFrames(0)
{
    setAction("ToggleDebugScreen",thor::Action(sf::Keyboard::F3,thor::Action::PressOnce));
    bind("ToggleDebugScreen",[&](ActionTarget::Context context){showDebugScreen(!isDebugScreenVisible());});

    setAction("CloseWindow",thor::Action(sf::Event::Closed));
    bind("CloseWindow",[&](ActionTarget::Context context){context.window->close();});

    setAction("TakeScreenShot",thor::Action(sf::Keyboard::F2,thor::Action::PressOnce));
    bind("TakeScreenShot",[&](ActionTarget::Context context){screenshot(); *this << "Screenshot saved !"; });
}

Application::~Application()
{
}

void Application::handleEvents()
{
    sf::Event event;
    while (Window::pollEvent(event))
    {
        ActionTarget::handleEvent(event);
        mStates.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
    mStates.update(dt);

    ActionTarget::update();

    mFpsFrames++;
    if (mFpsTimer.getElapsedTime() >= sf::seconds(1.0f))
    {
        DebugScreen::setDebugInfo("FPS",lp::to_string(mFpsFrames));
        mFpsTimer.restart();
        mFpsFrames = 0;
    }

    am::AudioManager::update();
}

void Application::render()
{
    Window::clear();
    Window::draw(mStates);
    Window::draw(*this); // Draw DebugScreen
    Window::display();
}

}
