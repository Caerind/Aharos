#ifndef SES_SPRITESYSTEM_HPP
#define SES_SPRITESYSTEM_HPP

#include <SFML/Graphics.hpp>
#include "../Components.hpp"
#include "../System.hpp"

namespace ses
{

class SpriteSystem : public System
{
    public:
        SpriteSystem();

        void render(sf::RenderTarget& target);
};

} // namespace ses

#endif // SES_SPRITESYSTEM_HPP
