#include "Window.hpp"

namespace ah
{

Window::Window()
{
    mTitle = "";
    mVerticalSync = false;
    mVisible = true;
    mKeyRepeat = true;
    mCursorVisibility = MouseCursor::Default;
    mScreenshotPath = "";
}

void Window::create(sf::VideoMode videoMode, std::string title, sf::Uint32 style)
{
    sf::RenderWindow::create(videoMode,title,style);
    mTitle = title;
}

void Window::setSize(sf::Vector2i size)
{
    sf::RenderWindow::setSize(static_cast<sf::Vector2u>(size));
}

sf::Vector2i Window::getSize()
{
    return static_cast<sf::Vector2i>(sf::RenderWindow::getSize());
}

void Window::setTitle(std::string title)
{
    sf::RenderWindow::setTitle(title);
    mTitle = title;
}

std::string Window::getTitle()
{
    return mTitle;
}

void Window::setDefaultView()
{
    return setView(getDefaultView());
}

void Window::display()
{
    if (mCursorVisibility == Window::MouseCursor::Custom)
    {
        setDefaultView();
        mCursor.setPosition(getMousePosition());
        draw(mCursor);
    }

    sf::RenderWindow::display();
}

void Window::setVerticalSyncEnabled(bool enabled)
{
    sf::RenderWindow::setVerticalSyncEnabled(enabled);
    mVerticalSync = enabled;
}

bool Window::isVerticalSyncEnabled()
{
    return mVerticalSync;
}

void Window::setVisible(bool visible)
{
    sf::RenderWindow::setVisible(visible);
}

bool Window::isVisible()
{
    return mVisible;
}

void Window::setKeyRepeatEnabled(bool enabled)
{
    sf::RenderWindow::setKeyRepeatEnabled(enabled);
    mKeyRepeat = enabled;
}

bool Window::isKeyRepeatEnabled()
{
    return mKeyRepeat;
}

void Window::setIcon(std::string const& filename)
{
    mIcon.loadFromFile(filename);
    sf::RenderWindow::setIcon(mIcon.getSize().x,mIcon.getSize().y,mIcon.getPixelsPtr());
}

void Window::setMousePosition2i(sf::Vector2i pos)
{
    sf::Mouse::setPosition(pos,*this);
}

void Window::setMousePosition(sf::Vector2f pos)
{
    sf::Mouse::setPosition(static_cast<sf::Vector2i>(pos),*this);
}

void Window::setMousePositionMap(sf::Vector2f pos)
{
    sf::Mouse::setPosition(mapCoordsToPixel(pos));
}

void Window::setMousePositionView(sf::Vector2f pos, sf::View const& view)
{
    sf::Mouse::setPosition(mapCoordsToPixel(pos,view));
}

sf::Vector2i Window::getMousePosition2i()
{
    return sf::Mouse::getPosition(*this);
}

sf::Vector2f Window::getMousePosition()
{
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this));
}

sf::Vector2f Window::getMousePositionMap()
{
    return mapPixelToCoords(sf::Mouse::getPosition(*this));
}

sf::Vector2f Window::getMousePositionView(sf::View const& view)
{
    return mapPixelToCoords(sf::Mouse::getPosition(*this),view);
}

void Window::hideMouseCursor()
{
    sf::RenderWindow::setMouseCursorVisible(false);
    mCursorVisibility = Window::MouseCursor::None;
}

void Window::useDefaultMouseCursor()
{
    sf::RenderWindow::setMouseCursorVisible(true);
    mCursorVisibility = Window::MouseCursor::Default;
}

void Window::useCustomMouseCursor()
{
    sf::RenderWindow::setMouseCursorVisible(false);
    mCursorVisibility = Window::MouseCursor::Custom;
}

Window::MouseCursor Window::getMouseCursorVisibility()
{
    return mCursorVisibility;
}

sf::Sprite& Window::getMouseCursor()
{
    return mCursor;
}

void Window::setMouseCursorTexture(std::string const& filename)
{
    mCursorTexture.loadFromFile(filename);
    mCursor.setTexture(mCursorTexture);
}

void Window::setMouseCursorTextureRect(sf::IntRect rect)
{
    mCursor.setTextureRect(rect);
}

void Window::setMouseCursorOrigin(sf::Vector2f origin)
{
    mCursor.setOrigin(origin);
}

void Window::screenshot()
{
    capture().saveToFile(mScreenshotPath + getTime("%Y-%m-%d_%H-%M-%S") + ".png");
}

void Window::setScreenshotPath(std::string const& screenshotPath)
{
    mScreenshotPath = screenshotPath;
}

std::string Window::getScreenshotPath() const
{
    return mScreenshotPath;
}

}
