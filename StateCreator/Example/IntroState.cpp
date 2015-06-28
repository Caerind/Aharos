#include "IntroState.hpp"

IntroState::IntroState(ah::StateManager& manager) : ah::State(manager)
{
    mType = IntroState::getID();
}

std::string IntroState::getID()
{
    return "IntroState";
}

bool IntroState::handleEvent(sf::Event const& event)
{
    return true;
}

bool IntroState::update(sf::Time dt)
{
    return true;
}

void IntroState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

void IntroState::onActivate()
{

}

void IntroState::onDeactivate()
{

}

void IntroState::ToMenu()
{

}
