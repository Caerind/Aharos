#ifndef AH_APPLICATION_HPP
#define AH_APPLICATION_HPP

#include <string>
#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include <Thor/Input.hpp>

#include "AudioManager.hpp"
#include "DebugScreen.hpp"
#include "Log.hpp"
#include "Math.hpp"
#include "ResourceHolder.hpp"
#include "StateManager.hpp"
#include "String.hpp"
#include "Window.hpp"

namespace ah
{

class Application : public Log, public ResourceHolder, public Window, public DebugScreen, public am::AudioManager
{
    public:
        static Application& instance();

        typedef thor::ActionMap<std::string> ActionMap;
        typedef thor::ActionMap<std::string>::CallbackSystem CallbackSystem;

        void run();

        ActionMap& getActionMap();
        CallbackSystem& getCallbackSystem();

        void setAction(std::string const& id, thor::Action action);
        bool isActionActive(std::string const& id);

        template <typename T>
        void registerState(std::string const& stateId);
        void pushState(std::string const& stateId);

    private:
        Application();
        ~Application();

        void handleEvents();
        void update(sf::Time dt);
        void render();

    private:
        static Application mInstance;

        StateManager mStates;

        sf::Time mFpsTimer;
        unsigned int mFpsFrames;

        ActionMap mActionMap;
        CallbackSystem mCallbackSystem;
};

template <typename T>
void Application::registerState(std::string const& stateId)
{
    mStates.registerState<T>(stateId);
}

}

#endif // AH_APPLICATION_HPP
