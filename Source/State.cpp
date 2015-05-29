#include "State.hpp"
#include "StateManager.hpp"
#include "Application.hpp"

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

std::string State::getType() const
{
    return mType;
}

Application& State::getApplication()
{
    return mManager.getApplication();
}

bool State::isActiveState() const
{
    return mType == mManager.getActiveStateType();
}
