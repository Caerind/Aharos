#include "State.hpp"
#include "StateManager.hpp"
#include "Application.hpp"

namespace ah
{

std::string State::getID()
{
    return "State";
}

State::State(StateManager& manager)
: mManager(manager)
, mType(State::getID())
{
}

State::~State()
{
}

bool State::handleEvent(sf::Event const& event)
{
    return true;
}

bool State::update(sf::Time dt)
{
    return true;
}

void State::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

std::string State::getType() const
{
    return mType;
}

bool State::isActiveState() const
{
    return mType == mManager.getActiveStateType();
}

Application& State::getApplication()
{
    return mManager.getApplication();
}

void State::onActivate()
{

}

void State::onDeactivate()
{

}

void State::requestPush(std::string const& id)
{
    mManager.pushState(id);
}

void State::requestPop()
{
    mManager.popState();
}

void State::requestClear()
{
    mManager.clearStates();
}

}
