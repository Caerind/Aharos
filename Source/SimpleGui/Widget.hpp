#ifndef SG_WIDGET_HPP
#define SG_WIDGET_HPP

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace sg
{

class Widget : public sf::Drawable, public sf::Transformable
{
    public:
        typedef std::shared_ptr<Widget> Ptr;

        Widget();
        Widget(Widget* parent);

        virtual void update(sf::Event const& event, sf::Vector2f mousePosition);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void setSize(sf::Vector2f size);
        sf::Vector2f getSize() const;

        sf::FloatRect getGlobalBounds() const;

        void setVisible(bool visible);
        bool isVisible() const;

        virtual void setEnabled(bool enabled);
        bool isEnabled() const;

        virtual void setActive(bool active);
        bool isActive() const;

        void setGlobalPosition(sf::Vector2f position);
        sf::Vector2f getGlobalPosition() const;

    protected:
        Widget* mParent;
        sf::Vector2f mSize;
        bool mVisible;
        bool mEnabled;
        bool mActive;
};

}

#endif // SG_WIDGET_HPP
