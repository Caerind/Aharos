#include "StateManager.hpp"

#include <cassert>

StateManager::StateManager()
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

void StateManager::render()
{
	for(auto itr = mStates.begin(); itr != mStates.end(); itr++)
	{
        (*itr)->render();
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

bool StateManager::isEmpty() const
{
	return mStates.empty();
}

std::size_t StateManager::getStatesCount() const
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

State::Ptr StateManager::createState(std::string const& id)
{
	auto found = mFactories.find(id);
	assert(found != mFactories.end());
	return found->second();
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

void StateManager::setData(std::string const& id, std::string const& data)
{
    mStringData[id] = data;
}

void StateManager::setData(std::string const& id, bool const& data)
{
    mBoolData[id] = data;
}

void StateManager::setData(std::string const& id, int const& data)
{
    mIntData[id] = data;
}

void StateManager::setData(std::string const& id, float const& data)
{
    mFloatData[id] = data;
}

void StateManager::setData(std::string const& id, sf::FloatRect const& data)
{
    mFloatRectData[id] = data;
}

void StateManager::setData(std::string const& id, sf::IntRect const& data)
{
    mIntRectData[id] = data;
}

void StateManager::setData(std::string const& id, sf::Vector2f const& data)
{
    mVectorFloatData[id] = data;
}

void StateManager::setData(std::string const& id, sf::Vector2i const& data)
{
    mVectorIntData[id] = data;
}

void StateManager::setData(std::string const& id, sf::Color const& data)
{
    mColorData[id] = data;
}

std::string StateManager::getStringData(std::string const& id)
{
    return mStringData[id];
}

bool StateManager::getBoolData(std::string const& id)
{
    return mBoolData[id];
}

int StateManager::getIntData(std::string const& id)
{
    return mIntData[id];
}

float StateManager::getFloatData(std::string const& id)
{
    return mFloatData[id];
}

sf::FloatRect StateManager::getFloatRectData(std::string const& id)
{
    return mFloatRectData[id];
}

sf::IntRect StateManager::getIntRectData(std::string const& id)
{
    return mIntRectData[id];
}

sf::Vector2f StateManager::getVectorFloatData(std::string const& id)
{
    return mVectorFloatData[id];
}

sf::Vector2i StateManager::getVectorIntData(std::string const& id)
{
    return mVectorIntData[id];
}

sf::Color StateManager::getColorData(std::string const& id)
{
    return mColorData[id];
}
