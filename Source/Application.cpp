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

    mFpsTimer += dt;
    mFpsFrames++;
    if (mFpsTimer >= sf::seconds(1.0f))
    {
        DebugScreen::setDebugInfo("FPS",to_string(mFpsFrames));
        mFpsTimer -= sf::seconds(1.0f);
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
