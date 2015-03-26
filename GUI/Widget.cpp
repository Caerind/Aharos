#include "Widget.hpp"

Widget::Widget()
: mParent(nullptr)
, mEnabled(true)
, mVisible(true)
, mActive(true)
, mSize(sf::Vector2f(0,0))
{
}

Widget::Widget(Widget* parent)
: mParent(parent)
, mEnabled(true)
, mVisible(true)
, mActive(true)
, mSize(sf::Vector2f(0,0))
{
}

bool Widget::isEnabled() const
{
    return mEnabled;
}

void Widget::enable()
{
    mEnabled = true;
}

void Widget::disable()
{
    mEnabled = false;
}

bool Widget::isVisible() const
{
    return mVisible;
}

void Widget::show()
{
    mVisible = true;
}

void Widget::hide()
{
    mVisible = false;
}

bool Widget::isActive() const
{
    return mActive;
}

void Widget::activate()
{
    mActive = true;
}

void Widget::deactivate()
{
    mActive = false;
}

sf::Vector2f Widget::getSize() const
{
    return mSize;
}

void Widget::setSize(sf::Vector2f size)
{
    mSize = size;
}

sf::Vector2f Widget::getGlobalPosition() const
{
    if (mParent != nullptr)
    {
        return getPosition() + mParent->getGlobalPosition();
    }
    return getPosition();
}

void Widget::setGlobalPosition(sf::Vector2f position)
{
    if (mParent != nullptr)
    {
        setPosition(position - mParent->getGlobalPosition());
    }
    else
    {
        setPosition(position);
    }
}

sf::FloatRect Widget::getGlobalBounds() const
{
    return sf::FloatRect(getGlobalPosition(),getSize());
}
