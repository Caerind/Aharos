#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

class Window : public sf::RenderWindow
{
    public:
        Window();

        //
        // Window Part
        //
    public:
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

        //
        // Icon
        //
    protected:
        void setIcon(std::string const& filename);

        //
        // Mouse
        //
    public:
        void setMousePosition2i(sf::Vector2i pos);
        void setMousePosition(sf::Vector2f pos);
        void setMousePositionMap(sf::Vector2f pos);
        void setMousePositionView(sf::Vector2f pos, sf::View const& view);
        sf::Vector2i getMousePosition2i();
        sf::Vector2f getMousePosition();
        sf::Vector2f getMousePositionMap();
        sf::Vector2f getMousePositionView(sf::View const& view);

        //
        // Cursor
        //
    public:
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
};

#endif // WINDOW_HPP
