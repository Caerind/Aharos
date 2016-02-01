#include "State.hpp"
#include "StateManager.hpp"

namespace ah
{

State::State(StateManager& manager, std::string const& type)
: mManager(manager)
, mType(type)
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

void State::render(sf::RenderTarget& target, sf::RenderStates states)
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

} // namespace ah
