#ifndef SES_SPRITECOMPONENT_HPP
#define SES_SPRITECOMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "../Component.hpp"

namespace ses
{

class SpriteComponent : public Component, public sf::Sprite
{
    public:
        SpriteComponent();

        void setTexture(std::string const& id);

        bool contains(sf::Vector2f const& position) const;
        sf::FloatRect getBounds() const;

        void load(pugi::xml_node& component);
        void save(pugi::xml_node& component);

    protected:
        std::string mTextureId;
};

} // namespace ses

#endif // SES_SPRITECOMPONENT_HPP
