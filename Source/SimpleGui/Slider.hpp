#ifndef SG_SLIDER_HPP
#define SG_SLIDER_HPP

#include "Box.hpp"

#include <iostream>

namespace sg
{

class Slider : public Box
{
    public:
        typedef std::shared_ptr<Slider> Ptr;

        Slider();
        Slider(Widget* parent);

        virtual void update(sf::Event const& event, sf::Vector2f mousePosition);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void setInterval(float a, float b);
        sf::Vector2f getInterval();

        void setValue(float value);
        float getValue();

        sf::RectangleShape& getShapeTop();

        void setVertical();
        void setHorizontal();
        bool isVertical();

    protected:
        void updateShapeTop();

    protected:
        sf::RectangleShape mShapeTop;
        sf::Vector2f mInterval;
        sf::Vector2f mOffset;
        bool mVertical;
};

}

#endif // SG_SLIDER_HPP
