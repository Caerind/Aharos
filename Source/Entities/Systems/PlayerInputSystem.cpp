#include "PlayerInputSystem.hpp"
#include "../World.hpp"

namespace ses
{

PlayerInputSystem::PlayerInputSystem() : System(), lp::ActionTarget(ah::Application::getBinding().getMap())
{
}

void PlayerInputSystem::setFunction(std::string const& id, std::function<void()> f)
{
    mFunctions[id] = f;
}

void PlayerInputSystem::removeFunction(std::string const& id)
{
    auto itr = mFunctions.find(id);
    if (itr != mFunctions.end())
    {
        mFunctions.erase(itr);
    }
}

void PlayerInputSystem::update()
{
    mMap->invokeCallbacks(mSystem,&(ah::Application::getWindow()));

    for (auto itr = mFunctions.begin(); itr != mFunctions.end(); itr++)
    {
        if (itr->second)
        {
            itr->second();
        }
    }

    mMap->clearEvents();
}

} // namespace ses
