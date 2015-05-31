#ifndef AH_MUSICMANAGER_HPP
#define AH_MUSICMANAGER_HPP

#include <memory>
#include <string>

#include <SFML/Audio/Music.hpp>

#include <Thor/Math/Random.hpp>

namespace ah
{

class MusicManager
{
    public:
        MusicManager();
        ~MusicManager();

        std::shared_ptr<sf::Music> playMusic(std::string const& filename);
        std::shared_ptr<sf::Music> playList();

        std::vector<std::string>& getPlaylist();

    protected:
        void updateMusicManager();

    private:
        std::shared_ptr<sf::Music> mMusic;
        std::vector<std::string> mFilenames;
        int mPlaylistIndex;
        bool mLoopMode;
};

}

#endif // AH_MUSICMANAGER_HPP
