#ifndef AH_APPLICATION_HPP
#define AH_APPLICATION_HPP

#include <string>
#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "ActionTarget.hpp"
#include "AudioManager.hpp"
#include "DebugScreen.hpp"
#include "Log.hpp"
#include "ResourceHolder.hpp"
#include "StateManager.hpp"
#include "../Helper/String.hpp"
#include "../Helper/TypeToString.hpp"
#include "Window.hpp"

namespace ah
{

class Application : public Log, public ResourceHolder, public Window, public DebugScreen, public am::AudioManager, public ActionTarget
{
    public:
        static Application& instance();

        void run();

        template <typename T>
        void registerState();

        template <typename T>
        void pushState();

    private:
        Application();
        ~Application();

        void handleEvents();
        void update(sf::Time dt);
        void render();

    private:
        static Application mInstance;

        StateManager mStates;

        sf::Clock mFpsTimer;
        unsigned int mFpsFrames;
};

template <typename T>
void Application::registerState()
{
    mStates.registerState<T>();
}

template <typename T>
void Application::pushState()
{
    mStates.pushState<T>();
}

} // namespace ah

#endif // AH_APPLICATION_HPP
