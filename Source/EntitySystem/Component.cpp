#include "Component.hpp"
#include "Entity.hpp"

namespace es
{

Component::Component()
{
    mParent = nullptr;
}

Component::~Component()
{
    mParent = nullptr;
}

std::string Component::getId()
{
    return "Component";
}

Entity* Component::getParent() const
{
    return mParent;
}

void Component::setParent(Entity* parent)
{
    mParent = parent;
}

EntityManager* Component::getManager() const
{
    if (hasParent())
    {
        return mParent->getManager();
    }
    return nullptr;
}

bool Component::hasParent() const
{
    return mParent != nullptr;
}

bool Component::hasManager() const
{
    if (hasParent())
    {
        if (mParent->getManager() != nullptr)
        {
            return true;
        }
    }
    return false;
}

std::size_t Component::getParentId() const
{
    if (hasParent())
    {
        return mParent->getId();
    }
    return 0;
}

} // namespace es
