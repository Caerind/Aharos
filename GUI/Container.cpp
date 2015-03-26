#include "Container.hpp"

Container::Container()
{
}

void Container::handleEvent(sf::Event const& event)
{
    if (isEnabled())
    {
        for (unsigned int i = 0; i < mWidgets.size(); i++)
        {
            if (mWidgets[i] != nullptr)
            {
                //mWidgets[i]->handleEvent(event);
            }
        }
    }
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isVisible())
    {
        states.transform *= getTransform();
        for (unsigned int i = 0; i < mWidgets.size(); i ++)
        {
            if (mWidgets[i] != nullptr)
            {
                //target.draw(*mWidgets[i],states);
            }
        }
    }
}
