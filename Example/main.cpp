#include <SFML/Graphics.hpp>
#include "../Source/Application.hpp"
#include "../Source/FileLogger.hpp"
#include "../Source/SoundManager.hpp"
#include "../Source/MusicManager.hpp"
#include "../Source/Window.hpp"
#include "../Source/Statistics.hpp"

#include "Example.hpp"

int main()
{
    Window::create(sf::VideoMode(800,600),"SFML window");
    Window::setMouseCursorTexture("Assets/cursor.png");
    Window::useCustomMouseCursor();

    FileLogger::open("Assets/sys.log");
    FileLogger::useConsole(true);
    FileLogger::write("Launched !");

    SoundManager::play("Assets/explosion.wav");
    MusicManager::getPlaylist()->push_back("Assets/gong.ogg");
    MusicManager::playList();

    Statistics::setFont("Assets/aniron.ttf");

    Application app;
    app.registerState<Example>(Example::getID());
    app.run(Example::getID());

    return EXIT_SUCCESS;
}
