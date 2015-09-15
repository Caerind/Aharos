#ifndef ES_COMPONENT_HPP
#define ES_COMPONENT_HPP

#include <map>
#include <string>

namespace es
{

class Entity;
class EntityManager;

class Component
{
    public:
        friend class Entity;

        Component();
        virtual ~Component();

        static std::string getId();

        Entity* getParent() const;
        void setParent(Entity* parent);
        EntityManager* getManager() const;
        bool hasParent() const;
        bool hasManager() const;
        std::size_t getParentId() const;

    protected:
        Entity* mParent;
};

typedef std::map<std::string,Component*> ComponentArray;

} // namespace es

#endif // ES_COMPONENT_HPP
