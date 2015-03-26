#ifndef MUSICMANAGER_HPP
#define MUSICMANAGER_HPP

#include <memory>
#include <string>

#include <SFML/Audio/Music.hpp>

class MusicManager
{
    public:
        static MusicManager* instance();

        static std::shared_ptr<sf::Music> playLoop(std::string const& filename);
        static std::shared_ptr<sf::Music> playList();

        static std::vector<std::string>* getPlaylist();

        static void update();

    private:
        MusicManager();
        ~MusicManager();

        static MusicManager gInstance;
        static bool gInitialised;

        std::shared_ptr<sf::Music> mMusic;
        bool mListMode;
        std::vector<std::string> mFilenames;
};

#endif // MUSICMANAGER_HPP
