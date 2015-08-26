#include "Renderable.hpp"

namespace rd
{

Renderable::Renderable() : mZ(0.f)
{
}

sf::FloatRect Renderable::getBounds()
{
    return sf::FloatRect();
}

void Renderable::render(sf::RenderTarget& target)
{
}

void Renderable::setPosition(sf::Vector2f const& position)
{
}

sf::Vector2f Renderable::getPosition() const
{
    return sf::Vector2f();
}

void Renderable::setZ(float z)
{
    mZ = z;
}

float Renderable::getZ() const
{
    return mZ;
}

} // namespace rd
