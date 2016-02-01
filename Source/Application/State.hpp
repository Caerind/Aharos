#ifndef AH_STATE_HPP
#define AH_STATE_HPP

#include <memory>
#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../Helper/TypeToString.hpp"

namespace ah
{

class StateManager;

class State : public sf::Transformable
{
    public:
        typedef std::unique_ptr<State> Ptr;

    public:
        State(StateManager& manager, std::string const& type = "State");
        virtual ~State();

        virtual bool handleEvent(sf::Event const& event);
        virtual bool update(sf::Time dt);
        virtual void render(sf::RenderTarget& target, sf::RenderStates states);

        std::string getType() const;
        bool isActiveState() const;

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

} // namespace ah

#endif // AH_STATE_HPP
