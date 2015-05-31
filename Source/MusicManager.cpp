#include "MusicManager.hpp"

namespace ah
{

MusicManager::MusicManager() : mLoopMode(true)
{
    mMusic = std::make_shared<sf::Music>();
}

MusicManager::~MusicManager()
{
    mMusic = nullptr;
}

std::shared_ptr<sf::Music> MusicManager::playMusic(std::string const& filename)
{
    mLoopMode = true;
    mMusic->setLoop(true);
    mMusic->stop();
    if (mMusic->openFromFile(filename))
    {
        mMusic->play();
    }
    return mMusic;
}

std::shared_ptr<sf::Music> MusicManager::playList()
{
    mLoopMode = false;
    mMusic->setLoop(false);
    mMusic->stop();
    mPlaylistIndex = -1;
    MusicManager::updateMusicManager();
    return mMusic;
}

std::vector<std::string>& MusicManager::getPlaylist()
{
    return mFilenames;
}

void MusicManager::updateMusicManager()
{
    if (!mLoopMode && mMusic->getStatus() == sf::Music::Status::Stopped)
    {
        mPlaylistIndex++;
        if (mPlaylistIndex == static_cast<int>(mFilenames.size()))
        {
            mPlaylistIndex = 0;
        }
        if (mMusic->openFromFile(mFilenames.at(mPlaylistIndex)))
        {
            mMusic->play();
        }
    }
}

}
