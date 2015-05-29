#include "Application.hpp"

Application::Application() : mStates(*this), mFpsFrames(0), mStatistics(true)
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
		if (mStatistics)
		{
            updateFps(dt);
        }
		render();
	}
}

void Application::enableStatistics(bool enable)
{
    mStatistics = enable;
}

bool Application::isStatisticsEnabled() const
{
    return mStatistics;
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
    Window::draw(mStates);
    if (mStatistics)
    {
        Statistics::render();
    }
    Window::display();
}

void Application::setData(std::string const& id, std::string const& data)
{
    mStringData[id] = data;
}

void Application::setData(std::string const& id, bool const& data)
{
    mBoolData[id] = data;
}

void Application::setData(std::string const& id, int const& data)
{
    mIntData[id] = data;
}

void Application::setData(std::string const& id, float const& data)
{
    mFloatData[id] = data;
}

void Application::setData(std::string const& id, sf::FloatRect const& data)
{
    mFloatRectData[id] = data;
}

void Application::setData(std::string const& id, sf::IntRect const& data)
{
    mIntRectData[id] = data;
}

void Application::setData(std::string const& id, sf::Vector2f const& data)
{
    mVectorFloatData[id] = data;
}

void Application::setData(std::string const& id, sf::Vector2i const& data)
{
    mVectorIntData[id] = data;
}

void Application::setData(std::string const& id, sf::Color const& data)
{
    mColorData[id] = data;
}

std::string Application::getStringData(std::string const& id)
{
    return mStringData[id];
}

bool Application::getBoolData(std::string const& id)
{
    return mBoolData[id];
}

int Application::getIntData(std::string const& id)
{
    return mIntData[id];
}

float Application::getFloatData(std::string const& id)
{
    return mFloatData[id];
}

sf::FloatRect Application::getFloatRectData(std::string const& id)
{
    return mFloatRectData[id];
}

sf::IntRect Application::getIntRectData(std::string const& id)
{
    return mIntRectData[id];
}

sf::Vector2f Application::getVectorFloatData(std::string const& id)
{
    return mVectorFloatData[id];
}

sf::Vector2i Application::getVectorIntData(std::string const& id)
{
    return mVectorIntData[id];
}

sf::Color Application::getColorData(std::string const& id)
{
    return mColorData[id];
}
