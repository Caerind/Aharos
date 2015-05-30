#include "MusicManager.hpp"

MusicManager::MusicManager()
{
    mMusic = std::make_shared<sf::Music>();
}

MusicManager::~MusicManager()
{
    mMusic = nullptr;
}

std::shared_ptr<sf::Music> MusicManager::playLoop(std::string const& filename)
{
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
    mMusic->setLoop(false);
    mMusic->stop();
    MusicManager::updateMusicManager();
    return mMusic;
}

std::vector<std::string>& MusicManager::getPlaylist()
{
    return mFilenames;
}

void MusicManager::updateMusicManager()
{
    if (!mMusic->getLoop() && mMusic->getStatus() == sf::Music::Status::Stopped)
    {
        int max = mFilenames.size()-1;
        if (mMusic->openFromFile(mFilenames.at(thor::random(0,max))))
        {
            mMusic->play();
        }
    }
}

