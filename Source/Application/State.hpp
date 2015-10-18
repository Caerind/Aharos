#ifndef AH_STATE_HPP
#define AH_STATE_HPP

#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../Helper/TypeToString.hpp"

namespace ah
{

class Application;
class StateManager;

class State : public sf::Drawable, public sf::Transformable
{
    public:
        typedef std::unique_ptr<State> Ptr;

    public:
        State(StateManager& manager, std::string const& type = "State");
        virtual ~State();

        virtual bool handleEvent(sf::Event const& event);
        virtual bool update(sf::Time dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        std::string getType() const;
        bool isActiveState() const;

        Application& getApplication();

        virtual void onActivate();
        virtual void onDeactivate();

    protected:
        void requestPush(std::string const& id);
        void requestPop();
        void requestClear();

    protected:
        StateManager& mManager;
        std::string mType;
};

}

#endif // AH_STATE_HPP
