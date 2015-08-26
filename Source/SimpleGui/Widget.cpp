#include "Widget.hpp"

namespace sg
{

Widget::Widget()
{
    mParent = nullptr;
    mSize = sf::Vector2f(0.f,0.f);
    mVisible = true;
    mEnabled = true;
    mActive = false;
}

Widget::Widget(Widget* parent)
{
    mParent = parent;
    mSize = sf::Vector2f(0.f,0.f);
    mVisible = true;
    mEnabled = true;
    mActive = false;
}

void Widget::update(sf::Event const& event, sf::Vector2f mousePosition)
{
}

void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Widget::setSize(sf::Vector2f size)
{
    mSize = size;
}

sf::Vector2f Widget::getSize() const
{
    return mSize;
}

sf::FloatRect Widget::getGlobalBounds() const
{
    return sf::FloatRect(getGlobalPosition(),mSize);
}

void Widget::setVisible(bool visible)
{
    mVisible = visible;
}

bool Widget::isVisible() const
{
    return mVisible;
}

void Widget::setEnabled(bool enabled)
{
    mEnabled = enabled;
}

bool Widget::isEnabled() const
{
    return mEnabled;
}

void Widget::setActive(bool active)
{
    mActive = active;
}

bool Widget::isActive() const
{
    return mActive;
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

sf::Vector2f Widget::getGlobalPosition() const
{
    if (mParent != nullptr)
    {
        return getPosition() + mParent->getGlobalPosition();
    }
    return getPosition();
}

}
