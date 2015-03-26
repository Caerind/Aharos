#include "Example.hpp"

Example::Example(StateManager& manager)
: State(manager)
{
    mType = Example::getID();
    auto t = ResourceHolder::get<sf::Texture>("Assets/cb.bmp");
    if (t != nullptr)
    {
        mSprite.setTexture(*t);
    }
    mSprite.setPosition(10,10);
}

std::string Example::getID()
{
    return "Example";
}

bool Example::handleEvent(sf::Event const& event)
{
    return true;
}

bool Example::update(sf::Time dt)
{
    return true;
}

void Example::render()
{
    Window::draw(mSprite);
}
