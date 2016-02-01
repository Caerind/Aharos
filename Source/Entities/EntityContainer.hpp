#ifndef SES_ENTITYCONTAINER_HPP
#define SES_ENTITYCONTAINER_HPP

#include <algorithm>
#include "ComponentFilter.hpp"
#include "Entity.hpp"

namespace ses
{

class EntityContainer : public ComponentFilter
{
    public:
        EntityContainer();
        ~EntityContainer();

        void update(Entity::Ptr entity);

        Entity::Ptr at(std::size_t index) const;
        Entity::Ptr get(std::string const& id);
        std::size_t size() const;
        bool contains(Entity::Ptr entity);
        bool contains(std::string const& id);
        void add(Entity::Ptr entity);
        void remove(Entity::Ptr entity);
        void removeAll();
        void sort(std::function<bool(Entity::Ptr,Entity::Ptr)> f);

    protected:
        EntityVector mEntities;
};

} // namespace ses

#endif // SES_ENTITYCONTAINER_HPP
