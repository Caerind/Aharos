#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <algorithm>
#include <memory>

class Entity;
class System;

class EntityManager
{
    public:
        friend class Entity;
        friend class System;

        typedef std::shared_ptr<Entity> EntityPtr;
        typedef std::vector<EntityPtr> EntityArray;
        typedef std::vector<System*> SystemArray;

    public:
        EntityManager();
        ~EntityManager();

        EntityPtr create(std::string const& name = "");

        EntityPtr get(std::size_t id);
        EntityPtr getByName(std::string const& name);
        EntityArray getByType(std::string const& type);
        EntityArray getByTag(std::string const& tag);

        void remove(EntityPtr e);
        void remove(std::size_t id);
        void removeByName(std::string const& name);
        void removeByType(std::string const& type);
        void removeByTag(std::string const& tag);

        void addSystem(System* system);
        void removeSystem(System* system);

    private:
        void update(std::size_t id);

        EntityPtr getEntity(std::size_t id);

    private:
        EntityArray mEntities;
        SystemArray mSystems;
};

#endif // ENTITYMANAGER_HPP
