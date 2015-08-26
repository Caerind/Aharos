#ifndef AH_WINDOW_HPP
#define AH_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

#include "Clock.hpp"

namespace ah
{

class Window : public sf::RenderWindow
{
    public:
        Window();

    public: // Window
        void create(sf::VideoMode videoMode, std::string title, sf::Uint32 style = sf::Style::Default);

        void setSize(sf::Vector2i size);
        sf::Vector2i getSize();

        void setTitle(std::string title);
        std::string getTitle();

        void setDefaultView();

        void display();

        void setVerticalSyncEnabled(bool enabled);
        bool isVerticalSyncEnabled();

        void setVisible(bool visible);
        bool isVisible();

        void setKeyRepeatEnabled(bool enabled);
        bool isKeyRepeatEnabled();

    public: // Icon
        void setIcon(std::string const& filename);

    public: // Mouse
        void setMousePosition2i(sf::Vector2i pos);
        void setMousePosition(sf::Vector2f pos);
        void setMousePositionMap(sf::Vector2f pos);
        void setMousePositionView(sf::Vector2f pos, sf::View const& view);
        sf::Vector2i getMousePosition2i();
        sf::Vector2f getMousePosition();
        sf::Vector2f getMousePositionMap();
        sf::Vector2f getMousePositionView(sf::View const& view);

    public: // Cursor
        enum MouseCursor
        {
            Default,
            None,
            Custom,
        };

        void hideMouseCursor();
        void useDefaultMouseCursor();
        void useCustomMouseCursor();
        MouseCursor getMouseCursorVisibility();

        sf::Sprite& getMouseCursor();
        void setMouseCursorTexture(std::string const& filename);
        void setMouseCursorTextureRect(sf::IntRect rect);
        void setMouseCursorOrigin(sf::Vector2f origin);

    public: // Screenshot
        void screenshot();
        void setScreenshotPath(std::string const& screenshotPath);
        std::string getScreenshotPath() const;

    private:
        // Window
        sf::RenderWindow mWindow;
        sf::Image mIcon;
        std::string mTitle;
        bool mVerticalSync;
        bool mVisible;
        bool mKeyRepeat;

        // Cursor
        MouseCursor mCursorVisibility;
        sf::Sprite mCursor;
        sf::Texture mCursorTexture;

        // Screenshot
        std::string mScreenshotPath;
};

}

#endif // AH_WINDOW_HPP
