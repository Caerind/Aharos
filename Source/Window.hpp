#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Source/ResourceHolder.hpp"

class Window
{
    public:
        static Window* instance();

        //
        // Window Part
        //
        static void create(sf::VideoMode videoMode, std::string title, sf::Uint32 style = sf::Style::Default);
        static bool isOpen();
        static void close();

        static void setSize(sf::Vector2i size);
        static sf::Vector2i getSize();

        static void setTitle(std::string title);
        static std::string getTitle();

        static bool pollEvent(sf::Event& event);
        static bool waitEvent(sf::Event& event);

        static void setPosition(sf::Vector2i position);
        static sf::Vector2i getPosition();

        static void setView(sf::View const& view);
        static void setDefaultView();
        static sf::View getView();
        static sf::View getDefaultView();

        static void draw(sf::Drawable const& drawable, sf::RenderStates const& states = sf::RenderStates::Default);
        static void draw(sf::Vertex* vertices, unsigned int vertexCount, sf::PrimitiveType type, sf::RenderStates const& states = sf::RenderStates::Default);
        static void clear(sf::Color const& color = sf::Color(0.f,0.f,0.f,255.f));
        static void display();

        static void setVerticalSyncEnabled(bool enabled);
        static bool isVerticalSyncEnabled();

        static void setVisible(bool visible);
        static bool isVisible();

        static void setKeyRepeatEnabled(bool enabled);
        static bool isKeyRepeatEnabled();

        static sf::Image capture();

        //
        // Icon
        //
        static void setIcon(std::string const& filename);

        //
        // Mouse
        //
        static void setMousePosition2i(sf::Vector2i pos);
        static void setMousePosition(sf::Vector2f pos);
        static void setMousePositionMap(sf::Vector2f pos);
        static void setMousePositionView(sf::Vector2f pos, sf::View const& view);
        static sf::Vector2i getMousePosition2i();
        static sf::Vector2f getMousePosition();
        static sf::Vector2f getMousePositionMap();
        static sf::Vector2f getMousePositionView(sf::View const& view);

        //
        // Cursor
        //
        enum MouseCursor
        {
            Default,
            None,
            Custom,
        };

        static void hideMouseCursor();
        static void useDefaultMouseCursor();
        static void useCustomMouseCursor();
        static MouseCursor getMouseCursorVisibility();

        static sf::Sprite* getMouseCursor();
        static void setMouseCursorTexture(std::string const& filename);
        static void setMouseCursorTextureRect(sf::IntRect rect);
        static void setMouseCursorOrigin(sf::Vector2f origin);

    private:
        Window();
        ~Window();

        static Window gInstance;
        static bool gInitialised;

        // Window
        sf::RenderWindow mWindow;
        std::string mTitle;
        bool mVerticalSync;
        bool mVisible;
        bool mKeyRepeat;

        // Cursor
        MouseCursor mCursorVisibility;
        sf::Sprite mCursor;
};

#endif // WINDOW_HPP
