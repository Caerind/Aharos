#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <memory>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

class Widget : public sf::Drawable, public sf::Transformable
{
    public:
        typedef std::shared_ptr<Widget> Ptr;

        Widget();
        Widget(Widget* parent);

        bool isEnabled() const;
        void enable();
        void disable();

        bool isVisible() const;
        void show();
        void hide();

        bool isActive() const;
        void activate();
        void deactivate();

        sf::Vector2f getSize() const;
        void setSize(sf::Vector2f size);

        sf::Vector2f getGlobalPosition() const;
        void setGlobalPosition(sf::Vector2f position);

        sf::FloatRect getGlobalBounds() const;

    protected:
        Widget* mParent;
        bool mEnabled;
        bool mVisible;
        bool mActive;
        sf::Vector2f mSize;
};

#endif // WIDGET_HPP
