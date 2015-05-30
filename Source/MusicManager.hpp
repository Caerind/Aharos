#ifndef MUSICMANAGER_HPP
#define MUSICMANAGER_HPP

#include <memory>
#include <string>

#include <SFML/Audio/Music.hpp>

#include <Thor/Math/Random.hpp>

class MusicManager
{
    public:
        MusicManager();
        ~MusicManager();

        std::shared_ptr<sf::Music> playLoop(std::string const& filename);
        std::shared_ptr<sf::Music> playList();

        std::vector<std::string>& getPlaylist();

    protected:
        void updateMusicManager();

    private:
        std::shared_ptr<sf::Music> mMusic;
        std::vector<std::string> mFilenames;
};

#endif // MUSICMANAGER_HPP
