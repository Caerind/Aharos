#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "Window.hpp"
#include "MusicManager.hpp"
#include "Statistics.hpp"

#include "StateManager.hpp"

class Application
{
    public:
        Application();

        template <typename T>
        void registerState(std::string const& stateId);

        void run(std::string const& stateId);

        void enableStatistics(bool enable);
        bool isStatisticsEnabled() const;

		void setData(std::string const& id, std::string const& data);
		void setData(std::string const& id, bool const& data);
		void setData(std::string const& id, int const& data);
		void setData(std::string const& id, float const& data);
		void setData(std::string const& id, sf::FloatRect const& data);
		void setData(std::string const& id, sf::IntRect const& data);
		void setData(std::string const& id, sf::Vector2f const& data);
		void setData(std::string const& id, sf::Vector2i const& data);
		void setData(std::string const& id, sf::Color const& data);

        std::string getStringData(std::string const& id);
        bool getBoolData(std::string const& id);
        int getIntData(std::string const& id);
        float getFloatData(std::string const& id);
        sf::FloatRect getFloatRectData(std::string const& id);
        sf::IntRect getIntRectData(std::string const& id);
        sf::Vector2f getVectorFloatData(std::string const& id);
        sf::Vector2i getVectorIntData(std::string const& id);
        sf::Color getColorData(std::string const& id);

    private:
        void handleEvents();
        void update(sf::Time dt);
        void updateFps(sf::Time dt);
        void render();

    private:
        StateManager mStates;

        sf::Time mFpsTimer;
        unsigned int mFpsFrames;

        bool mStatistics;

        // Data
		std::map<std::string,std::string> mStringData;
		std::map<std::string,bool> mBoolData;
		std::map<std::string,int> mIntData;
		std::map<std::string,float> mFloatData;
		std::map<std::string,sf::FloatRect> mFloatRectData;
		std::map<std::string,sf::IntRect> mIntRectData;
		std::map<std::string,sf::Vector2f> mVectorFloatData;
		std::map<std::string,sf::Vector2i> mVectorIntData;
		std::map<std::string,sf::Color> mColorData;
};

template <typename T>
void Application::registerState(std::string const& stateId)
{
    mStates.registerState<T>(stateId);
}

#endif // APPLICATION_HPP
