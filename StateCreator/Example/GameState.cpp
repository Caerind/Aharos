#include "GameState.hpp"

GameState::GameState(ah::StateManager& manager) : ah::State(manager)
{
    mType = GameState::getID();
}

std::string GameState::getID()
{
    return "GameState";
}

bool GameState::handleEvent(sf::Event const& event)
{
    return true;
}

bool GameState::update(sf::Time dt)
{
    return true;
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

void GameState::onActivate()
{

}

void GameState::onDeactivate()
{

}

void GameState::ToMenu()
{

}
