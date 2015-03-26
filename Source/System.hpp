#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include <algorithm>

#include "Component.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

class System
{
    public:
        typedef std::vector<Entity::Ptr> EntityArray;

    public:
        System();
        System(EntityManager* manager);
        virtual ~System();

        void add(Entity::Ptr e);
        void remove(Entity::Ptr e);
        bool contains(Entity::Ptr e);
        bool hasRequiredComponents(Entity::Ptr e);
        EntityArray getEntities();

    private:
        EntityManager* mManager;
        EntityArray mEntities;
        ComponentFilter mFilter;
};

#endif // SYSTEM_HPP
