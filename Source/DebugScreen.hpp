#ifndef DEBUGSCREEN_HPP
#define DEBUGSCREEN_HPP

#include <map>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

class DebugScreen : public sf::Drawable
{
    public:
        DebugScreen();

        void setDebugInfo(std::string const& id, std::string const& value);

        void showDebugScreen();
        void hideDebugScreen();
        bool isDebugScreenVisible();

    protected:
        void setFont(sf::Font& font);
        void setCharsize(std::size_t charsize);

        void update();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::shared_ptr<sf::Font> mFont;
        std::size_t mCharsize;
        bool mShowDebugScreen;
        std::map<std::string,sf::Text> mValues;
};

#endif // DEBUGSCREEN_HPP
