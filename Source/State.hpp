#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../Source/Window.hpp"

class StateManager;

class State
{
    public:
        static std::string getID();

        typedef std::unique_ptr<State> Ptr;

    public:
        State(StateManager& manager);
        virtual ~State();

        virtual bool handleEvent(sf::Event const& event);
        virtual bool update(sf::Time dt);
        virtual void render();

        std::string getType() const;
        bool isActiveState() const;

    protected:
        void requestPush(std::string const& id);
        void requestPop();
        void requestClear();

    protected:
        StateManager& mManager;
        std::string mType;
};

#endif // STATE_HPP
