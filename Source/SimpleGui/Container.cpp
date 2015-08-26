#include "Container.hpp"

namespace sg
{

Container::Container()
{
    mVisible = true;
}

void Container::update(sf::Event const& event, sf::Vector2f mousePosition)
{
    if (mVisible)
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

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mVisible)
    {
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

void Container::update()
{
    if (mVisible)
    {
        for (unsigned int i = 0; i < mDynamics.size(); i++)
        {
            if (mDynamics[i] != nullptr)
            {
                mDynamics[i]->update(sf::Event(),sf::Vector2f(0,0));
            }
        }
    }
}

bool Container::isVisible() const
{
    return mVisible;
}

void Container::setVisible(bool visible)
{
    mVisible = visible;
}

}
