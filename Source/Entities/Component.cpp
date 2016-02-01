#include "Component.hpp"
#include "Entity.hpp"

namespace ses
{

Component::Component() : mEntity(nullptr)
{
}

Component::~Component()
{
    mEntity = nullptr;
}

void Component::load(pugi::xml_node& node)
{
}

void Component::save(pugi::xml_node& node)
{
}

} // namespace ses
