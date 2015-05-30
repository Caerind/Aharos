#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "DataManager.hpp"
#include "DebugScreen.hpp"
#include "FileLogger.hpp"
#include "ResourceHolder.hpp"

#include "Window.hpp"
#include "MusicManager.hpp"
#include "Statistics.hpp"
#include "String.hpp"
#include "StateManager.hpp"

class Application : public FileLogger, public ResourceHolder, public DebugScreen, public DataManager
{
    public:
        Application();

        void run(std::string const& stateId);

    private:
        void handleEvents();
        void update(sf::Time dt);
        void render();

        template <typename T>
        void registerState(std::string const& stateId);

    private:
        StateManager mStates;

        sf::Time mFpsTimer;
        unsigned int mFpsFrames;
};

template <typename T>
void Application::registerState(std::string const& stateId)
{
    mStates.registerState<T>(stateId);
}

#endif // APPLICATION_HPP
