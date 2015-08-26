#ifndef SG_TIMER_HPP
#define SG_TIMER_HPP

#include <sstream>
#include <iostream>

#include <Thor/Time/Timer.hpp>

#include "Box.hpp"

namespace sg
{

class Timer : public Box, public thor::Timer
{
    public:
        typedef std::shared_ptr<Timer> Ptr;

        Timer();
        Timer(Widget* parent);

        virtual void update(sf::Event const& event, sf::Vector2f mousePosition);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void reset(sf::Time timeLimit);
        void restart(sf::Time timeLimit);

        sf::RectangleShape& getShapeTop();

    protected:
        sf::Time mTimeLimit;
        sf::RectangleShape mShapeTop;
};

}

#endif // SG_TIMER_HPP
