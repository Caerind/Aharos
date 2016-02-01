#ifndef SES_COMPONENTFILTER_HPP
#define SES_COMPONENTFILTER_HPP

#include <memory>
#include <string>
#include <vector>

#include "../Helper/TypeToString.hpp"

namespace ses
{

class Entity;

class ComponentFilter
{
    public:
        ComponentFilter();
        ~ComponentFilter();

        template <typename T>
        void requires();
        void requires(std::string const& componentId);
        void requiresOne(std::vector<std::string> componentIds);

        template <typename T>
        void excludes();
        void excludes(std::string const& componentId);

        bool passFilter(Entity* entity) const;

    protected:
        std::vector<std::string> mRequiredComponents;
        std::vector<std::string> mExcludedComponents;
        std::vector<std::vector<std::string>> mRequiredOneComponents;
};

template <typename T>
void ComponentFilter::requires()
{
    requires(lp::type<T>());
}

template <typename T>
void ComponentFilter::excludes()
{
    excludes(lp::type<T>());
}

} // namespace ses

#endif // SES_COMPONENTFILTER_HPP
