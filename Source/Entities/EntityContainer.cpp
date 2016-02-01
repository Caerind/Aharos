#include "EntityContainer.hpp"

namespace ses
{

EntityContainer::EntityContainer()
{
}

EntityContainer::~EntityContainer()
{
    removeAll();
}

void EntityContainer::update(Entity::Ptr entity)
{
    if (entity != nullptr)
    {
        if (contains(entity))
        {
            if (!passFilter(entity.get()))
            {
                remove(entity);
            }
        }
        else
        {
            if (passFilter(entity.get()))
            {
                add(entity);
            }
        }
    }
}

Entity::Ptr EntityContainer::at(std::size_t index) const
{
    if (index >= 0 && index <= mEntities.size())
    {
        return mEntities.at(index);
    }
}

Entity::Ptr EntityContainer::get(std::string const& id)
{
    std::size_t s = mEntities.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mEntities[i]->getId() == id)
        {
            return mEntities[i];
        }
    }
    return nullptr;
}

std::size_t EntityContainer::size() const
{
    return mEntities.size();
}

bool EntityContainer::contains(Entity::Ptr entity)
{
    if (entity != nullptr)
    {
        return contains(entity->getId());
    }
    return false;
}

bool EntityContainer::contains(std::string const& id)
{
    std::size_t s = mEntities.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mEntities[i]->getId() == id)
        {
            return true;
        }
    }
    return false;
}

void EntityContainer::add(Entity::Ptr entity)
{
    if (entity != nullptr)
    {
        mEntities.push_back(entity);
    }
}

void EntityContainer::remove(Entity::Ptr entity)
{
    if (entity != nullptr)
    {
        for (std::size_t i = 0; i < mEntities.size(); i++)
        {
            if (mEntities[i]->getId() == entity->getId())
            {
                mEntities.erase(mEntities.begin() + i);
            }
        }
    }
}

void EntityContainer::removeAll()
{
    mEntities.clear();
}

void EntityContainer::sort(std::function<bool(Entity::Ptr,Entity::Ptr)> f)
{
    std::sort(mEntities.begin(),mEntities.end(),f);
}

} // namespace ses
