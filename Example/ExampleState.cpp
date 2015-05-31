#include "ExampleState.hpp"
#include "../Source/Application.hpp"

ExampleState::ExampleState(ah::StateManager& manager)
: State(manager)
{
    mType = ExampleState::getID();
    mSprite.setTexture(getApplication().getTexture("Assets/cb.bmp"));
    mSprite.setPosition(300,300);
    getApplication().setAction("quit",thor::Action(sf::Event::Closed));
}

std::string ExampleState::getID()
{
    return "ExampleState";
}

bool ExampleState::update(sf::Time dt)
{
    if (getApplication().isActionActive("quit"))
    {
        getApplication().close();
    }

    return true;
}

void ExampleState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
}
