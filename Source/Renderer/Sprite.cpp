#include "Sprite.hpp"

namespace rd
{

Sprite::Sprite() : Renderable(), sf::Sprite()
{
}

sf::FloatRect Sprite::getBounds()
{
    return sf::Sprite::getGlobalBounds();
}

void Sprite::render(sf::RenderTarget& target)
{
    target.draw(*this);
}

void Sprite::setPosition(sf::Vector2f const& position)
{
    sf::Sprite::setPosition(position);
}

sf::Vector2f Sprite::getPosition() const
{
    return sf::Sprite::getPosition();
}

} // namespace rd
