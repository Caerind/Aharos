#ifndef SES_COMPONENT_HPP
#define SES_COMPONENT_HPP

#include <memory>

#include "../Helper/pugixml.hpp"

namespace ses
{

class Entity;

class Component
{
    public:
        Component();
        virtual ~Component();

        typedef std::unique_ptr<Component> Ptr;

        virtual void load(pugi::xml_node& node);
        virtual void save(pugi::xml_node& node);

        friend Entity;

    protected:
        Entity* mEntity;
};

} // namespace ses

#endif // SES_COMPONENT_HPP
