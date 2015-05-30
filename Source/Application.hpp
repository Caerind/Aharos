#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include <Thor/Input.hpp>

#include "DataManager.hpp"
#include "DebugScreen.hpp"
#include "FileLogger.hpp"
#include "Lang.hpp"
#include "MusicManager.hpp"
#include "ResourceHolder.hpp"
#include "SoundManager.hpp"
#include "StateManager.hpp"
#include "String.hpp"
#include "Window.hpp"

class Application : public FileLogger, public ResourceHolder, public Window, public DebugScreen, public DataManager, public Lang, public MusicManager, public SoundManager
{
    public:
        Application();

        typedef thor::ActionMap<std::string> ActionMap;
        typedef thor::ActionMap<std::string>::CallbackSystem CallbackSystem;

        void run();

        ActionMap& getActionMap();
        CallbackSystem& getCallbackSystem();

        void setAction(std::string const& id, thor::Action action);
        bool isActionActive(std::string const& id);

        //TODO
        //void connect(...);

    protected:
        template <typename T>
        void registerState(std::string const& stateId);

        void pushState(std::string const& stateId);

    private:
        void handleEvents();
        void update(sf::Time dt);
        void render();

    private:
        StateManager mStates;

        ActionMap mActionMap;
        CallbackSystem mCallbackSystem;

        sf::Time mFpsTimer;
        unsigned int mFpsFrames;
};

template <typename T>
void Application::registerState(std::string const& stateId)
{
    mStates.registerState<T>(stateId);
}

#endif // APPLICATION_HPP
