#include "CheckBox.hpp"

namespace sg
{

CheckBox::CheckBox() : Box()
{
}

CheckBox::CheckBox(Widget* parent) : Box(parent)
{
}

void CheckBox::update(sf::Event const& event, sf::Vector2f mousePosition)
{
    if (mEnabled && mVisible)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && getGlobalBounds().contains(mousePosition))
        {
            setActive(!mActive);
            if (mCallbacks.size() >= 1)
                if (mCallbacks[0])
                    mCallbacks[0]();
        }
    }
}

}
