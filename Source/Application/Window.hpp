#ifndef AH_WINDOW_HPP
#define AH_WINDOW_HPP

#include <map>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../Helper/pugixml.hpp"
#include "../Helper/Time.hpp"

namespace ah
{

class Window : public sf::RenderWindow
{
    public:
        Window();
        ~Window();

        void setDefaultView();

        void clear();
        void display();

        //
        // SETTINGS
        //
        void create();
        void create(sf::VideoMode videoMode, std::string const& title, sf::Uint32 style = sf::Style::Close);
        void close();
        bool isFullscreen() const;
        void setFullscreen(bool full, sf::Uint32 style = sf::Style::Close);
        sf::VideoMode getVideoMode() const;
        void setVideoMode(sf::VideoMode const& videoMode);
        sf::Uint32 getStyle() const;
        void setStyle(sf::Uint32 style);


        void setTitle(std::string const& title);
        std::string getTitle() const;

        void setVerticalSyncEnabled(bool enabled);
        bool isVerticalSyncEnabled() const;

        void setVisible(bool visible);
        bool isVisible() const;

        void setKeyRepeatEnabled(bool enabled);
        bool isKeyRepeatEnabled() const;

        //
        // ICON
        //
        void setIcon(std::string const& filename);
        void setIcon(sf::Image* image);

        //
        // MOUSE
        //
        void setMousePosition2i(sf::Vector2i const& position);
        void setMousePosition(sf::Vector2f const& position);
        void setMousePositionMap(sf::Vector2f const& position);
        void setMousePositionView(sf::Vector2f const& position, sf::View const& view);
        sf::Vector2i getMousePosition2i() const;
        sf::Vector2f getMousePosition() const;
        sf::Vector2f getMousePositionMap() const;
        sf::Vector2f getMousePositionView(sf::View const& view);

        //
        // CURSOR
        //
        enum MouseCursor
        {
            Default,
            None,
            Custom,
        };

        void setMouseCursor(MouseCursor cursor);
        void hideMouseCursor();
        void useDefaultMouseCursor();
        void useCustomMouseCursor(sf::Texture* texture = nullptr, sf::Vector2f const& origin = sf::Vector2f(), sf::IntRect const& textureRect = sf::IntRect());
        MouseCursor getMouseCursor() const;

        sf::Sprite& getMouseCursorSprite();
        void setMouseCursorTexture(std::string const& filename);
        void setMouseCursorTexture(sf::Texture* texture);
        void setMouseCursorTextureRect(sf::IntRect const& textureRect);
        void setMouseCursorOrigin(sf::Vector2f const& origin);

        //
        // SCREENSHOT
        //
        void screenshot();
        void setScreenshotPath(std::string const& screenshotPath);
        std::string getScreenshotPath() const;

        //
        // DEBUG INFO
        //
        void showDebugInfo(bool visible);
        bool isDebugInfoVisible() const;
        void setDebugInfo(std::string const& id, std::string const& value);
        std::string getDebugInfo(std::string const& id) const;
        void setDebugInfoFont(std::string const& filename);
        void setDebugInfoFont(sf::Font* font);
        void setDebugInfoColor(sf::Color const& color);
        void setDebugInfoCharsize(std::size_t charsize);
        void removeDebugInfo(std::string const& id);
        void removeDebugInfos();

        //
        // LOADING/SAVING SETTINGS
        //
        bool load();
        void detect();
        void save();

        //
        // BACKGROUND
        //
        void setBackgroundColor(sf::Color color);
        void setBackgroundTexture(sf::Texture* texture, sf::IntRect rect = sf::IntRect());

    protected:
        void updateDebugInfo();
        void updateBackground();

    protected:
        std::string mTitle;
        bool mVerticalSync;
        bool mVisible;
        bool mKeyRepeat;
        sf::VideoMode mVideoMode;
        sf::Uint32 mStyle;

        sf::Image mIcon;

        MouseCursor mCursor;
        sf::Sprite mCursorSprite;
        sf::Texture mCursorTexture;

        std::string mScreenshotPath;

        bool mDebugInfoVisible;
        std::map<std::string,sf::Text> mDebugInfo;
        sf::Font mDebugInfoFont;
        sf::Color mDebugInfoColor;
        std::size_t mDebugInfoCharsize;

        sf::RectangleShape mBackground;


};

} // namespace ah

#endif // AH_WINDOW_HPP
