#ifndef ARROW_HPP
#define ARROW_HPP

#include <cmath>

#include "State.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Arrow : public sf::Drawable
{
    public:
        Arrow(State* state1, sf::Vector2f d1, State* state2, sf::Vector2f d2);

        void update();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        State* mState1;
        sf::Vector2f mDelta1;

        State* mState2;
        sf::Vector2f mDelta2;

        sf::RectangleShape mLine;
        sf::RectangleShape mLeft;
        sf::RectangleShape mRight;
};

#endif // ARROW_HPP
