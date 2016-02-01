#include "Application/Application.hpp"
#include "States/States.hpp"
#include "Helper/KeyBinding.hpp"

#include "Helper/Compression.hpp"

int main()
{
    pugi::xml_document doc;
    doc.load_file("prefabs.xml");
    lp::saveCompressedXml("prefabs.xmlx",doc);

    //lp::loadCompressedXml("prefabs.xmlx",doc2);

    //std::cout << doc2.child("Prefab").attribute("id").as_string() << std::endl;

    /*
    doc.load_file("test.xml");
    lp::saveCompressedXml("test.xmlx",doc);
    */

    ah::Application::getResources().loadImage("icon","Assets/Textures/icon.png");

    ah::Application::getResources().loadTexture("icon","Assets/Textures/icon.png");
    ah::Application::getResources().loadTexture("bg","Assets/Textures/back.png");
    ah::Application::getResources().loadTexture("cursor","Assets/Textures/cursor.png");
    ah::Application::getResources().loadTexture("libs","Assets/Textures/libs.png");
    ah::Application::getResources().loadTexture("ld","Assets/Textures/ld.png");
    ah::Application::getResources().loadTexture("tiles","Assets/Textures/tiles.png");

    ah::Application::getResources().getTexture("ld").setSmooth(true);
    ah::Application::getResources().getTexture("libs").setSmooth(true);
    ah::Application::getResources().getTexture("bg").setSmooth(true);

    ah::Application::getResources().loadFont("cool","Assets/Fonts/coolveticca.ttf");
    ah::Application::getResources().loadFont("atmog","Assets/Fonts/atmogFont.ttf");

    ah::Application::getResources().loadSoundBuffer("jingle","Assets/Sounds/jingleAtmog.wav");

    ah::Application::getWindow().setTitle("Aharos");
    ah::Application::getWindow().create();
    ah::Application::getWindow().setIcon(&ah::Application::getResources().getImage("icon"));
    ah::Application::getWindow().setDebugInfoFont(&ah::Application::getResources().getFont("cool"));
    ah::Application::getWindow().showDebugInfo(true);

    registerStates();

    ah::Application::getStates().pushState<GameState>();

    ah::Application::getAudio().playMusic("Assets/Musics/theme.ogg");

    ah::Application::getLang().setLang("Francais");
    //ah_Log << ah::Application::getLang().get("Play");

    ah::Application::run();

    return 0;
}
