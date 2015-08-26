#include "ActionTarget.hpp"
#include "Application.hpp"

namespace ah
{

ActionTarget::ActionTarget(ActionTarget::ActionMapPtr map)
{
    if (map == nullptr)
    {
        mMap = std::make_shared<thor::ActionMap<std::string>>();
    }
    else
    {
        mMap = map;
    }
}

void ActionTarget::handleEvent(sf::Event const& event)
{
    mMap->pushEvent(event);
}

void ActionTarget::update()
{
    mMap->invokeCallbacks(mSystem,&(ah::Application::instance()));
    mMap->clearEvents();
}

void ActionTarget::setAction(std::string const& key, thor::Action const& action)
{
	(*mMap)[key] = action;
}

const thor::Action& ActionTarget::getAction(std::string const& key)
{
	return (*mMap)[key];
}

bool ActionTarget::isActive(std::string const& key)
{
    return mMap->isActive(key);
}

void ActionTarget::bind(std::string const& key, Callback const& callback)
{
	mConnections[key] = mSystem.connect(key,callback);
}

void ActionTarget::unbind(std::string const& key)
{
    mConnections[key].disconnect();
}

} // namespace ah
