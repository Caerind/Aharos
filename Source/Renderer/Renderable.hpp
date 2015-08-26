#ifndef RD_RENDERABLE_HPP
#define RD_RENDERABLE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace rd
{

class Renderable
{
    public:
        Renderable();

        virtual sf::FloatRect getBounds() = 0;
        virtual void render(sf::RenderTarget& target) = 0;
        virtual void setPosition(sf::Vector2f const& position);
        virtual sf::Vector2f getPosition() const;

        void setZ(float z);
        float getZ() const;

    protected:
        float mZ;
};

} // namespace rd

#endif // RD_RENDERABLE_HPP
