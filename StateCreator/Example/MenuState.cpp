#include "MenuState.hpp"

MenuState::MenuState(ah::StateManager& manager) : ah::State(manager)
{
    mType = MenuState::getID();
}

std::string MenuState::getID()
{
    return "MenuState";
}

bool MenuState::handleEvent(sf::Event const& event)
{
    return true;
}

bool MenuState::update(sf::Time dt)
{
    return true;
}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

void MenuState::onActivate()
{

}

void MenuState::onDeactivate()
{

}

void MenuState::ToGame()
{

}

void MenuState::ToEnd()
{

}
