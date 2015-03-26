#ifndef BOX_HPP
#define BOX_HPP

#include "Widget.hpp"

#include <array>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Box : public Widget
{
    public:
        Box();

        enum TextAlign
        {
            Left,
            Center,
            Right,
        };

        void setFixedSize(sf::Vector2f size);
        void setFixedSize();
        void setSmartSize();

        void setTexture(sf::Texture& texture);
        void setTextureRect(unsigned int id, sf::IntRect rect);

        void setOutline(float thickness, sf::Color color);
        void setFillColor(unsigned int id, sf::Color fillColor);

        std::string getString() const;
        unsigned int getCharacterSize() const;
        sf::Color getTextColor() const;
        void setFont(sf::Font& font);
        void setString(std::string const& str);
        void setCharacterSize(unsigned int size);
        void setTextColor(sf::Color color);

        TextAlign getTextAlign() const;
        void setTextAlign(TextAlign align);

        void setCallback(unsigned int id, ...);
        void callback(unsigned int id);

    protected:
        void update();

    protected:
        bool mFixeSized;
        sf::Vector2f mFixedSize;
        bool mSmartSize;

        bool mUseSprite;
        sf::Sprite mSprite;
        std::array<sf::IntRect,3> mRects;

        bool mUseRect;
        sf::RectangleShape mShape;
        std::array<sf::Color,3> mColors;

        bool mUseText;
        sf::Text mText;
        TextAlign mAlign;

        //std::array<,2> mCallbacks;
};

#endif // BOX_HPP
