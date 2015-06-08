#include "Application.hpp"

namespace ah
{

Application::Application() : mStates(*this), mFpsFrames(0)
{
}

Application::~Application()
{
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
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			handleEvents();
			update(TimePerFrame);

			if (mStates.empty())
                close();

			std::cout << std::flush;
		}

		render();
	}
}

Application::ActionMap& Application::getActionMap()
{
    return mActionMap;
}

Application::CallbackSystem& Application::getCallbackSystem()
{
    return mCallbackSystem;
}

void Application::setAction(std::string const& id, thor::Action action)
{
    mActionMap[id] = action;
}

bool Application::isActionActive(std::string const& id)
{
    return mActionMap.isActive(id);
}

void Application::pushState(std::string const& stateId)
{
    mStates.pushState(stateId);
}

void Application::handleEvents()
{
    mActionMap.clearEvents();

    sf::Event event;
    while (Window::pollEvent(event))
    {
        mActionMap.pushEvent(event);
        mStates.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
    mStates.update(dt);

    mActionMap.invokeCallbacks(mCallbackSystem,this);

    mFpsTimer += dt;
    mFpsFrames++;
    if (mFpsTimer >= sf::seconds(1.0f))
    {
        DebugScreen::setDebugInfo("FPS",to_string(mFpsFrames));
        mFpsTimer -= sf::seconds(1.0f);
        mFpsFrames = 0;
    }

    MusicManager::updateMusicManager();
}

void Application::render()
{
    Window::clear();
    Window::draw(mStates);
    Window::draw(*this);
    Window::display();
}

}
