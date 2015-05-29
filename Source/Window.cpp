#include "Window.hpp"

Window Window::gInstance;
bool Window::gInitialised;

Window* Window::instance()
{
    return gInitialised ? &gInstance : nullptr;
}

void Window::create(sf::VideoMode videoMode, std::string title, sf::Uint32 style)
{
    if (instance() != nullptr)
    {
        instance()->mWindow.create(videoMode,title,style);
        instance()->mTitle = title;
    }
}

bool Window::isOpen()
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.isOpen();
    }
    return false;
}

void Window::close()
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.close();
    }
}

void Window::setSize(sf::Vector2i size)
{
    if (instance() != nullptr)
    {
        instance()->mWindow.setSize(static_cast<sf::Vector2u>(size));
    }
}

sf::Vector2i Window::getSize()
{
    if (instance() != nullptr)
    {
        return static_cast<sf::Vector2i>(instance()->mWindow.getSize());
    }
    return sf::Vector2i(0,0);
}

void Window::setTitle(std::string title)
{
    if (instance() != nullptr)
    {
        instance()->setTitle(title);
        instance()->mTitle = title;
    }
}

std::string Window::getTitle()
{
    if (instance() != nullptr)
    {
        return instance()->mTitle;
    }
    return "";
}

bool Window::pollEvent(sf::Event& event)
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.pollEvent(event);
    }
    return false;
}

bool Window::waitEvent(sf::Event& event)
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.waitEvent(event);
    }
    return false;
}

void Window::setPosition(sf::Vector2i position)
{
    if (instance() != nullptr)
    {
        instance()->mWindow.setPosition(position);
    }
}

sf::Vector2i Window::getPosition()
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.getPosition();
    }
    return sf::Vector2i(0,0);
}

void Window::setView(sf::View const& view)
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.setView(view);
    }
}

void Window::setDefaultView()
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.setView(Window::getDefaultView());
    }
}

sf::View Window::getView()
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.getView();
    }
    return sf::View();
}

sf::View Window::getDefaultView()
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.getDefaultView();
    }
    return sf::View();
}

void Window::draw(sf::Drawable const& drawable, sf::RenderStates const& states)
{
    if (instance() != nullptr)
    {
        instance()->mWindow.draw(drawable,states);
    }
}

void Window::draw(sf::Vertex* vertices, unsigned int vertexCount, sf::PrimitiveType type, sf::RenderStates const& states)
{
    if (instance() != nullptr)
    {
        instance()->mWindow.draw(vertices,vertexCount,type,states);
    }
}

void Window::clear(sf::Color const& color)
{
    if (instance() != nullptr)
    {
        instance()->mWindow.clear(color);
    }
}

void Window::display()
{
    if (instance() != nullptr)
    {
        if (instance()->mCursorVisibility == Window::MouseCursor::Custom)
        {
            Window::setDefaultView();
            instance()->mCursor.setPosition(Window::getMousePosition());
            instance()->mWindow.draw(instance()->mCursor);
        }

        instance()->mWindow.display();
    }
}

void Window::setVerticalSyncEnabled(bool enabled)
{
    if (instance() != nullptr)
    {
        instance()->mWindow.setVerticalSyncEnabled(enabled);
        instance()->mVerticalSync = enabled;
    }
}

bool Window::isVerticalSyncEnabled()
{
    if (instance() != nullptr)
    {
        return instance()->mVerticalSync;
    }
    return false;
}

void Window::setVisible(bool visible)
{
    if (instance() != nullptr)
    {
        instance()->mWindow.setVisible(visible);
        instance()->mVisible = visible;
    }
}

bool Window::isVisible()
{
    if (instance() != nullptr)
    {
        return instance()->mVisible;
    }
    return false;
}

void Window::setKeyRepeatEnabled(bool enabled)
{
    if (instance() != nullptr)
    {
        instance()->mWindow.setKeyRepeatEnabled(enabled);
        instance()->mKeyRepeat = enabled;
    }
}

bool Window::isKeyRepeatEnabled()
{
    if (instance() != nullptr)
    {
        return instance()->mKeyRepeat;
    }
    return false;
}

sf::Image Window::capture()
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.capture();
    }
    return sf::Image();
}

void Window::setIcon(std::string const& filename)
{
    if (instance() != nullptr)
    {
        auto i = ResourceHolder::get<sf::Image>(filename);
        if (i != nullptr)
        {
            instance()->mWindow.setIcon(i->getSize().x,i->getSize().y,i->getPixelsPtr());
        }
    }
}

void Window::setMousePosition2i(sf::Vector2i pos)
{
    if (instance() != nullptr)
    {
        sf::Mouse::setPosition(pos,instance()->mWindow);
    }
}

void Window::setMousePosition(sf::Vector2f pos)
{
    if (instance() != nullptr)
    {
        sf::Mouse::setPosition(static_cast<sf::Vector2i>(pos),instance()->mWindow);
    }
}

void Window::setMousePositionMap(sf::Vector2f pos)
{
    if (instance() != nullptr)
    {
        sf::Mouse::setPosition(instance()->mWindow.mapCoordsToPixel(pos));
    }
}

void Window::setMousePositionView(sf::Vector2f pos, sf::View const& view)
{
    if (instance() != nullptr)
    {
        sf::Mouse::setPosition(instance()->mWindow.mapCoordsToPixel(pos,view));
    }
}

sf::Vector2i Window::getMousePosition2i()
{
    if (instance() != nullptr)
    {
        return sf::Mouse::getPosition(instance()->mWindow);
    }
    return sf::Vector2i(0,0);
}

sf::Vector2f Window::getMousePosition()
{
    if (instance() != nullptr)
    {
        return static_cast<sf::Vector2f>(sf::Mouse::getPosition(instance()->mWindow));
    }
    return sf::Vector2f(0,0);
}

sf::Vector2f Window::getMousePositionMap()
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.mapPixelToCoords(sf::Mouse::getPosition(instance()->mWindow));
    }
    return sf::Vector2f(0,0);
}

sf::Vector2f Window::getMousePositionView(sf::View const& view)
{
    if (instance() != nullptr)
    {
        return instance()->mWindow.mapPixelToCoords(sf::Mouse::getPosition(instance()->mWindow),view);
    }
    return sf::Vector2f(0,0);
}

void Window::hideMouseCursor()
{
    if (instance() != nullptr)
    {
        instance()->mWindow.setMouseCursorVisible(false);
        instance()->mCursorVisibility = Window::MouseCursor::None;
    }
}

void Window::useDefaultMouseCursor()
{
    if (instance() != nullptr)
    {
        instance()->mWindow.setMouseCursorVisible(true);
        instance()->mCursorVisibility = Window::MouseCursor::Default;
    }
}

void Window::useCustomMouseCursor()
{
    if (instance() != nullptr)
    {
        instance()->mWindow.setMouseCursorVisible(false);
        instance()->mCursorVisibility = Window::MouseCursor::Custom;
    }
}

Window::MouseCursor Window::getMouseCursorVisibility()
{
    if (instance() != nullptr)
    {
        return instance()->mCursorVisibility;
    }
    return Window::MouseCursor::Default;
}

sf::Sprite* Window::getMouseCursor()
{
    if (instance() != nullptr)
    {
        return &instance()->mCursor;
    }
    return nullptr;
}

void Window::setMouseCursorTexture(std::string const& filename)
{
    if (instance() != nullptr)
    {
        auto t = ResourceHolder::get<sf::Texture>(filename);
        if (t != nullptr)
        {
            instance()->mCursor.setTexture(*t);
        }
    }
}

void Window::setMouseCursorTextureRect(sf::IntRect rect)
{
    if (instance() != nullptr)
    {
        instance()->mCursor.setTextureRect(rect);
    }
}

void Window::setMouseCursorOrigin(sf::Vector2f origin)
{
    if (instance() != nullptr)
    {
        instance()->mCursor.setOrigin(origin);
    }
}

Window::Window()
{
    gInitialised = true;
    mTitle = "";
    mVerticalSync = false;
    mVisible = true;
    mKeyRepeat = true;
    mCursorVisibility = MouseCursor::Default;
}

Window::~Window()
{
    gInitialised = false;
}

