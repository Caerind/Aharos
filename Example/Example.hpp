#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

#include "../Source/State.hpp"

class Example : public State
{
    public:
        Example(StateManager& manager);

        static std::string getID();

        typedef std::unique_ptr<Example> Ptr;

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render();

    private:
        sf::Sprite mSprite;
};

#endif // EXAMPLE_HPP
