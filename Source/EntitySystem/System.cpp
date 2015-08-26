#include "System.hpp"

namespace es
{

System::System()
{
    mManager = nullptr;
}

System::~System()
{
    mManager = nullptr;
}

std::string System::getId()
{
    return "System";
}

ComponentFilter System::getFilter()
{
    return mFilter;
}

bool System::has(Entity::Ptr e)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i] == e)
        {
            return true;
        }
    }
    return false;
}

void System::add(Entity::Ptr e)
{
    if (e != nullptr)
    {
        if (e->hasComponents(mFilter) && !has(e))
        {
            mEntities.push_back(e);
        }
    }
}

void System::remove(Entity::Ptr e)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i] == e)
        {
            mEntities.erase(mEntities.begin() + i);
        }
    }
}

EntityManager* System::getManager() const
{
    return mManager;
}

bool System::hasManager() const
{
    return mManager != nullptr;
}

void System::requestRemove(Entity::Ptr e)
{
    if (hasManager())
    {
        mManager->remove(e);
    }
}

} // namespace es
