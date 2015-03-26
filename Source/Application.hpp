#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "Window.hpp"
#include "MusicManager.hpp"
#include "Statistics.hpp"

#include "StateManager.hpp"

class Application
{
    public:
        Application();

        template <typename T>
        void registerState(std::string const& stateId);

        void run(std::string const& stateId);

    private:
        void handleEvents();
        void update(sf::Time dt);
        void updateFps(sf::Time dt);
        void render();

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
