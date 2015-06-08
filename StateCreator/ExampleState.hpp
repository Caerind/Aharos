#ifndef EXAMPLESTATE_HPP
#define EXAMPLESTATE_HPP

#include "../Aharos/State.hpp"

class ExampleState : public ah::State
{
    public:
        ExampleState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // EXAMPLESTATE_HPP
