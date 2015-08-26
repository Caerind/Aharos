#include "Entity.hpp"

namespace es
{

std::size_t Entity::gIdCounter = 0;

Entity::Entity()
{
    mId = gIdCounter++;
}

bool Entity::hasComponent(std::string const& type) const
{
    return mComponents.find(type) != mComponents.end();
}

bool Entity::hasComponents(ComponentFilter const& filter)
{
    return filter.passFilter(this);
}

void Entity::removeComponents()
{
    for (auto itr = mComponents.begin(); itr != mComponents.end(); itr++)
    {
        delete itr->second;
        itr->second = nullptr;
    }
    if (hasManager())
    {
        mManager->updateEntity(mId,EntityManager::UpdateEntity::RemoveComponents);
    }
}

std::size_t Entity::getId() const
{
    return mId;
}

EntityManager* Entity::getManager() const
{
    return mManager;
}

bool Entity::hasManager() const
{
    return mManager != nullptr;
}

} // namespace es
