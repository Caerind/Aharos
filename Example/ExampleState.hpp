#ifndef EXAMPLESTATE_HPP
#define EXAMPLESTATE_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "../Source/Application/State.hpp"

class ExampleState : public ah::State
{
    public:
        ExampleState(ah::StateManager& manager);

        static std::string getID();

        typedef std::unique_ptr<ExampleState> Ptr;

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite mSprite;
        bool mExploded;
};

#endif // EXAMPLESTATE_HPP
