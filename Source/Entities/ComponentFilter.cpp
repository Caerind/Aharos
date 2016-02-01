#include "ComponentFilter.hpp"
#include "Entity.hpp"

namespace ses
{

ComponentFilter::ComponentFilter()
{
}

ComponentFilter::~ComponentFilter()
{
    mRequiredComponents.clear();
    mExcludedComponents.clear();
    mRequiredOneComponents.clear();
}

void ComponentFilter::requires(std::string const& componentId)
{
    mRequiredComponents.push_back(componentId);
}

void ComponentFilter::requiresOne(std::vector<std::string> componentIds)
{
    mRequiredOneComponents.push_back(componentIds);
}

void ComponentFilter::excludes(std::string const& componentId)
{
    mExcludedComponents.push_back(componentId);
}

bool ComponentFilter::passFilter(Entity* entity) const
{
    // Check if the entity is valid
    if (entity == nullptr)
    {
        return false;
    }

    // Check if the entity has all required components
    for (std::size_t i = 0; i < mRequiredComponents.size(); i++)
    {
        if (!entity->hasComponent(mRequiredComponents.at(i)))
        {
            return false;
        }
    }

    // Check if the entity doesn't have any excluded components
    for (std::size_t i = 0; i < mExcludedComponents.size(); i++)
    {
        if (entity->hasComponent(mExcludedComponents.at(i)))
        {
            return false;
        }
    }

    // Check if the entity has at least one of the required components on the list
    for (std::size_t i = 0; i < mRequiredOneComponents.size(); i++)
    {
        bool found = false;
        for (std::size_t j = 0; j < mRequiredOneComponents.at(i).size(); j++)
        {
            if (entity->hasComponent(mRequiredOneComponents.at(i).at(j)))
            {
                found = true;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}

} // namespace ses
