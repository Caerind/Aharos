#include "Window.hpp"

namespace sg
{

Window::Window() : Box()
{
}

Window::Window(Widget* parent) : Box(parent)
{
}

void Window::update(sf::Event const& event, sf::Vector2f mousePosition)
{
    if (mEnabled && mVisible)
    {
        for (unsigned int i = 0; i < mWidgets.size(); i++)
        {
            if (mWidgets[i] != nullptr)
            {
                mWidgets[i]->update(event,mousePosition);
            }
        }
    }
}

void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mVisible)
    {
        states.transform *= getTransform();
        target.draw(mShape,states);
        target.draw(mText,states);
        for (unsigned int i = 0; i < mWidgets.size(); i++)
        {
            if (mWidgets[i] != nullptr)
            {
                if (mWidgets[i]->isVisible())
                {
                    target.draw(*mWidgets[i],states);
                }
            }
        }
    }
}

void Window::updateText()
{
    mText.setPosition(sf::Vector2f(getGlobalBounds().width/2 - mText.getGlobalBounds().width/2,mPadding));
}

}
