#ifndef EXAMPLESTATE_HPP
#define EXAMPLESTATE_HPP

#include "../Source/State.hpp"

class ExampleState : public State
{
    public:
        ExampleState(StateManager& manager);

        static std::string getID();

        typedef std::unique_ptr<ExampleState> Ptr;

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite mSprite;
};

#endif // EXAMPLESTATE_HPP
