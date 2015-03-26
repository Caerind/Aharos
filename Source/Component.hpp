#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <vector>
#include <map>

class Component
{
    public:
        Component();
        virtual ~Component();

        static std::string getId();
};

typedef std::map<std::string,Component*> ComponentArray;
typedef std::vector<std::string> ComponentFilter;

#endif // COMPONENT_HPP
