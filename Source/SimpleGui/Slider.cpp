#include "Slider.hpp"

namespace sg
{

Slider::Slider() : Box()
{
    mVertical = false;
}

Slider::Slider(Widget* parent) : Box(parent)
{
    mVertical = false;
}

void Slider::update(sf::Event const& event, sf::Vector2f mousePosition)
{
    if (mVisible && mEnabled)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mShapeTop.getGlobalBounds().contains(mousePosition-getPosition()))
        {
            mOffset = mousePosition - mShapeTop.getPosition();
            setActive(true);
            if (mCallbacks.size() >= 2)
                if (mCallbacks[1])
                    mCallbacks[1]();
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && mActive)
        {
            setActive(false);
            if (mCallbacks.size() >= 2)
                if (mCallbacks[1])
                    mCallbacks[1]();
        }
        if (mActive)
        {
            sf::Vector2f pos;
            if (!mVertical)
            {
                pos.x = mousePosition.x - mOffset.x;
                pos.x = std::max(0.f,pos.x);
                pos.x = std::min(pos.x,getSize().x);
                pos.y = mShapeTop.getPosition().y;
            }
            if (mVertical)
            {
                pos.x = mShapeTop.getPosition().x;
                pos.y = std::max(0.f,pos.y);
                pos.y = std::min(pos.y,getSize().y);
                pos.y = mousePosition.y - mOffset.y;
            }
            mShapeTop.setPosition(pos);

            // Use to auto-update GUI which render the value
            if (mCallbacks.size() >= 1)
                if (mCallbacks[0])
                    mCallbacks[0]();
        }
    }
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mVisible)
    {
        states.transform *= getTransform();
        target.draw(mShape,states);
        target.draw(mShapeTop,states);
    }
}

void Slider::setInterval(float min, float max)
{
    mInterval.x = min;
    mInterval.y = max;
}

sf::Vector2f Slider::getInterval()
{
    return mInterval;
}

void Slider::setValue(float value)
{
    if (mInterval.y-mInterval.x != 0 && ((mInterval.y >= value && mInterval.x <= value) || (mInterval.y <= value && mInterval.x >= value)))
    {
        if (mVertical)
        {
            float y = getSize().y * value / (mInterval.y-mInterval.x);
            y = std::max(0.f,y);
            y = std::min(y,getSize().y);
            mShapeTop.setPosition(mShapeTop.getPosition().x,y);
        }
        else
        {
            float x = getSize().x * value / (mInterval.y-mInterval.x);
            x = std::max(0.f,x);
            x = std::min(x,getSize().x);
            mShapeTop.setPosition(x,mShapeTop.getPosition().y);
        }
    }
}

float Slider::getValue()
{
    float pos;
    float size;

    if (mVertical)
    {
        pos = std::max(0.f,mShapeTop.getPosition().y);
        size = getSize().y;
        pos = std::min(pos,size);
    }
    else
    {
        pos = std::max(0.f,mShapeTop.getPosition().x);
        size = getSize().x;
        pos = std::min(pos,size);
    }

    if (size != 0)
        return (mInterval.y-mInterval.x) * pos / size;
    return 0;
}

sf::RectangleShape& Slider::getShapeTop()
{
    return mShapeTop;
}

void Slider::setVertical()
{
    mVertical = true;
    //updateShapeTop();
}

void Slider::setHorizontal()
{
    mVertical = false;
    //updateShapeTop();
}

bool Slider::isVertical()
{
    return mVertical;
}

void Slider::updateShapeTop()
{
    if (!mVertical)
    {
        mShapeTop.setSize(sf::Vector2f(mShapeTop.getSize().x,getSize().y));
        mShapeTop.setOrigin(sf::Vector2f(mShapeTop.getSize().x/2,0));
    }
    if (mVertical)
    {
        mShapeTop.setSize(sf::Vector2f(getSize().x,mShapeTop.getSize().y));
        mShapeTop.setOrigin(sf::Vector2f(0,mShapeTop.getSize().y/2));
    }
}

}
