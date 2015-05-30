#include "ExampleState.hpp"
#include "Application.hpp"

ExampleState::ExampleState(StateManager& manager)
: State(manager)
{
    mType = ExampleState::getID();
}

std::string ExampleState::getID()
{
    return "ExampleState";
}

bool ExampleState::update(sf::Time dt)
{
    return true;
}

void ExampleState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
}
