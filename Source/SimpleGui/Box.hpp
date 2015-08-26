#ifndef SG_BOX_HPP
#define SG_BOX_HPP

#include <functional>
#include <string>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Widget.hpp"

namespace sg
{

class Box : public Widget
{
    public:
        typedef std::shared_ptr<Box> Ptr;

        enum TextAlign
        {
            Left,
            Center,
            Right,
        };

        Box();
        Box(Widget* parent);

        virtual void update(sf::Event const& event, sf::Vector2f mousePosition);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void setEnabled(bool enabled);
        void setActive(bool active);

        void setTexture(sf::Texture& texture);
        void setTextureRect(sf::IntRect rect, std::size_t id = 0);
        void setOutlineThickness(float thickness);
        void setOutlineColor(sf::Color color);
        void setFillColor(sf::Color color, std::size_t id = 0);
        void setSize(sf::Vector2f size);

        void setFont(sf::Font& font);
        void setTextColor(sf::Color color);
        virtual void setString(std::string const& string);
        void setCharacterSize(std::size_t charsize);
        void setTextAlign(TextAlign align);
        void setPadding(float padding);

        void setCallback(std::function<void()> callback, std::size_t id = 0);

        sf::RectangleShape& getShape();
        sf::Text& getText();

    protected:
        virtual void updateShape();
        virtual void updateText();

    protected:
        sf::RectangleShape mShape;
        sf::Text mText;
        TextAlign mAlign;
        float mPadding;
        bool mUsingSprite;
        std::vector<sf::IntRect> mTextureRects; // 0 : Normal, 1 : Active, 2 : Disabled
        std::vector<sf::Color> mFillColors; // 0 : Normal, 1 : Active, 2 : Disabled
        std::vector<std::function<void()>> mCallbacks; // 0 : Clic, 1 : In/Out
};

}

#endif // SG_BOX_HPP
