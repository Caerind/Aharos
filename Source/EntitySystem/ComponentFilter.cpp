#include "ComponentFilter.hpp"
#include "Entity.hpp"

namespace es
{

ComponentFilter::ComponentFilter()
{
}

void ComponentFilter::requires(std::string const& componentId)
{
    mRequiredComponents.push_back(componentId);
}

void ComponentFilter::excludes(std::string const& componentId)
{
    mExcludedComponents.push_back(componentId);
}

bool ComponentFilter::passFilter(Entity* entity) const
{
    if (entity == nullptr)
    {
        return false;
    }

    for (unsigned int i = 0; i < mRequiredComponents.size(); i++)
    {
        if (!entity->hasComponent(mRequiredComponents[i]))
        {
            return false;
        }
    }
    for (unsigned int i = 0; i < mExcludedComponents.size(); i++)
    {
        if (entity->hasComponent(mExcludedComponents[i]))
        {
            return false;
        }
    }
    return true;
}

} // namespace es
