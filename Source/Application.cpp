#include "Application.hpp"

Application::Application()
{
    Statistics::add("FPS","0");
}

void Application::run(std::string const& stateId)
{
    mStates.pushState(stateId);

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	while (Window::isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			handleEvents();
			update(TimePerFrame);

			if (mStates.isEmpty())
                Window::close();

			std::cout << std::flush;
		}
		updateFps(dt);
		render();
	}
}

void Application::handleEvents()
{
    sf::Event event;
    while (Window::pollEvent(event))
    {
        mStates.handleEvent(event);
        if (event.type == sf::Event::Closed)
        {
            Window::close();
        }
    }
}

void Application::update(sf::Time dt)
{
    mStates.update(dt);
    MusicManager::update();
}

void Application::updateFps(sf::Time dt)
{
    mFpsTimer += dt;
    mFpsFrames++;
    if (mFpsTimer >= sf::seconds(1.0f))
    {
        Statistics::setValue("FPS",std::to_string(mFpsFrames));
        mFpsTimer -= sf::seconds(1.0f);
        mFpsFrames = 0;
    }
}

void Application::render()
{
    Window::clear();
    mStates.render();
    Statistics::render();
    Window::display();
}
