#ifndef RD_SPRITE_HPP
#define RD_SPRITE_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Renderable.hpp"

namespace rd
{

class Sprite : public Renderable, public sf::Sprite
{
    public:
        Sprite();

        sf::FloatRect getBounds();
        void render(sf::RenderTarget& target);

        void setPosition(sf::Vector2f const& position);
        sf::Vector2f getPosition() const;
};

} // namespace rd

#endif // RD_SPRITE_HPP
