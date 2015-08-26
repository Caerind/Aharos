#ifndef ES_COMPONENTFILTER_HPP
#define ES_COMPONENTFILTER_HPP

#include <string>
#include <vector>

#include "Component.hpp"

namespace es
{

class Entity;

class ComponentFilter
{
    public:
        ComponentFilter();

        void requires(std::string const& componentId);
        void excludes(std::string const& componentId);

        bool passFilter(Entity* entity) const;

    protected:
        std::vector<std::string> mRequiredComponents;
        std::vector<std::string> mExcludedComponents;
};

} // namespace es

#endif // ES_COMPONENTFILTER_HPP
