#include "ExampleState.hpp"
#include "App.hpp"

ExampleState::ExampleState(ah::StateManager& manager) : ah::State(manager)
{
    mType = ExampleState::getID();
}

std::string ExampleState::getID()
{
    return "ExampleState";
}

bool ExampleState::handleEvent(sf::Event const& event)
{
    return true;
}

bool ExampleState::update(sf::Time dt)
{
    return true;
}

void ExampleState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}
