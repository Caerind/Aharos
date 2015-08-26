#ifndef ES_SYSTEM_HPP
#define ES_SYSTEM_HPP

#include <vector>

#include "Component.hpp"
#include "ComponentFilter.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

namespace es
{

class System
{
    public:
        friend class EntityManager;

    public:
        System();
        virtual ~System();

        static std::string getId();

        ComponentFilter getFilter();

        bool has(Entity::Ptr e);
        void add(Entity::Ptr e);
        void remove(Entity::Ptr e);

        EntityManager* getManager() const;
        bool hasManager() const;
        void requestRemove(Entity::Ptr e);

    protected:
        ComponentFilter mFilter;
        EntityManager* mManager;
        EntityArray mEntities;
};

} // namespace es

#endif // ES_SYSTEM_HPP
