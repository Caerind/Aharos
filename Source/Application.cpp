#include "Application.hpp"

Application::Application() : FileLogger("sys.log"), ResourceHolder(), DebugScreen(), mStates(*this), mFpsFrames(0)
{
}

void Application::run(std::string const& stateId)
{
    mStates.pushState(stateId);

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

			if (mStates.isEmpty())
                close();

			std::cout << std::flush;
		}

		render();
	}
}

void Application::handleEvents()
{
    sf::Event event;
    while (pollEvent(event))
    {
        mStates.handleEvent(event);
        if (event.type == sf::Event::Closed)
        {
            close();
        }
    }
}

void Application::update(sf::Time dt)
{
    mStates.update(dt);

    mFpsTimer += dt;
    mFpsFrames++;
    if (mFpsTimer >= sf::seconds(1.0f))
    {
        setDebugInfo("FPS",to_string(mFpsFrames));
        mFpsTimer -= sf::seconds(1.0f);
        mFpsFrames = 0;
    }

    //MusicManager::update();
}

void Application::render()
{
    clear();
    draw(mStates);
    DebugScreen::render(*this);
    display();
}
