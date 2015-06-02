#ifndef AH_APPLICATION_HPP
#define AH_APPLICATION_HPP

#include <string>
#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include <Thor/Input.hpp>

#include "DataManager.hpp"
#include "DebugScreen.hpp"
#include "Lang.hpp"
#include "Log.hpp"
#include "MusicManager.hpp"
#include "ResourceHolder.hpp"
#include "SoundManager.hpp"
#include "StateManager.hpp"
#include "String.hpp"
#include "Window.hpp"

namespace ah
{

class Application : public Log, public ResourceHolder, public Window, public DebugScreen, public DataManager, public Lang, public MusicManager, public SoundManager
{
    public:
        Application();
        virtual ~Application();

        typedef thor::ActionMap<std::string> ActionMap;
        typedef thor::ActionMap<std::string>::CallbackSystem CallbackSystem;

        void run();

        ActionMap& getActionMap();
        CallbackSystem& getCallbackSystem();

        void setAction(std::string const& id, thor::Action action);
        bool isActionActive(std::string const& id);

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

        sf::Time mFpsTimer;
        unsigned int mFpsFrames;

    protected:
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
