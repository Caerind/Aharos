#include "StateManager.hpp"
#include "State.hpp"
#include "Application.hpp"

#include <cassert>

namespace ah
{

StateManager::StateManager(Application& app) : mApplication(app)
{
}

StateManager::PendingChange::PendingChange(Action action, std::string const& id)
: action(action)
, id(id)
{
}

void StateManager::handleEvent(sf::Event const& event)
{
	for(auto itr = mStates.rbegin(); itr != mStates.rend(); itr++)
	{
		if(!(*itr)->handleEvent(event))
			break;
	}

    applyPendingChanges();
}

void StateManager::update(sf::Time dt)
{
	for(auto itr = mStates.rbegin(); itr != mStates.rend(); itr++)
	{
		if(!(*itr)->update(dt))
			break;
	}

    applyPendingChanges();
}

void StateManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto itr = mStates.begin(); itr != mStates.end(); itr++)
	{
        target.draw(*(*itr));
	}
}

void StateManager::pushState(std::string const& id)
{
	mPendingList.push_back(PendingChange(Push, id));
}

void StateManager::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

void StateManager::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool StateManager::empty() const
{
	return mStates.empty();
}

std::size_t StateManager::size() const
{
	return mStates.size();
}

std::string StateManager::getActiveStateType() const
{
    if (!mStates.empty())
    {
        return mStates.back()->getType();
    }
    return "";
}

std::string StateManager::getLastActiveStateType() const
{
    return mLastActiveStateType;
}

Application& StateManager::getApplication()
{
    return mApplication;
}

void StateManager::applyPendingChanges()
{
    for(PendingChange change : mPendingList)
	{
		switch(change.action)
		{
			case Action::Push:
                if (!mStates.empty())
                {
                    mLastActiveStateType = mStates.back()->getType();
                }
				mStates.push_back(createState(change.id));
				break;

			case Action::Pop:
                if (!mStates.empty())
                {
                    mLastActiveStateType = mStates.back()->getType();
                }
				mStates.pop_back();
				break;

			case Action::Clear:
                if (!mStates.empty())
                {
                    mLastActiveStateType = mStates.back()->getType();
                }
                mStates.clear();
                break;
		}
	}
	mPendingList.clear();
}

State::Ptr StateManager::createState(std::string const& id)
{
	auto found = mFactories.find(id);
	assert(found != mFactories.end());
	return found->second();
}


}
