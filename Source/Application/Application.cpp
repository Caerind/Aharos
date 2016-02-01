#include "Application.hpp"

namespace ah
{

Application Application::mInstance;

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    sf::Time timePerFrame = sf::seconds(1/60.f);
    sf::Clock fpsClock;
    std::size_t fps = 0;
    mInstance.mWindow.setDebugInfo("FPS","0");
    while (mInstance.mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;

            sf::Event event;
            while (mInstance.mWindow.pollEvent(event))
            {
                mInstance.mStates.handleEvent(event);

                if (event.type == sf::Event::Closed)
                {
                    mInstance.mWindow.close();
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3)
                {
                    mInstance.mWindow.showDebugInfo(!mInstance.mWindow.isDebugInfoVisible());
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
                {
                    mInstance.mWindow.screenshot();
                }
            }

            mInstance.mStates.update(timePerFrame);
            if (mInstance.mStates.empty())
            {
                mInstance.mWindow.close();
            }
            mInstance.mAudio.update();
        }

        mInstance.mWindow.clear();
        mInstance.mStates.render(mInstance.mWindow,sf::RenderStates());
        mInstance.mWindow.display();

        fps++;
        if (fpsClock.getElapsedTime() >= sf::seconds(1.f))
        {
            mInstance.mWindow.setDebugInfo("FPS",std::to_string(fps));
            fps = 0;
            fpsClock.restart();
        }
    }
}

StateManager& Application::getStates()
{
    return mInstance.mStates;
}

Window& Application::getWindow()
{
    return mInstance.mWindow;
}

AudioManager& Application::getAudio()
{
    return mInstance.mAudio;
}

ResourceManager& Application::getResources()
{
    return mInstance.mResources;
}

LangManager& Application::getLang()
{
    return mInstance.mLang;
}

Log& Application::getLog()
{
    return mInstance.mLog;
}

lp::KeyBinding& Application::getBinding()
{
    return mInstance.mBinding;
}

Application::Application()
{
}

Application::~Application()
{
}

} // namespace ah
