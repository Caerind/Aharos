#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <functional>
#include <map>
#include <vector>

#include "State.hpp"

class StateManager
{
    public:
		StateManager();

		template<typename T>
		void registerState(std::string const& id);

		void handleEvent(sf::Event const& event);
		void update(sf::Time dt);
		void render();

		void pushState(std::string const& id);
		void popState();
		void clearStates();

		bool isEmpty() const;
		std::size_t getStatesCount() const;
		std::string getActiveStateType() const;
		std::string getLastActiveStateType() const;

		void applyPendingChanges();

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
		enum Action
		{
			Push,
			Pop,
			Clear
		};

		struct PendingChange
		{
			explicit PendingChange(Action action, std::string const& id = "");
			Action action;
			std::string id;
		};

	private:
		State::Ptr createState(std::string const& id);

		std::string mLastActiveStateType;

		std::vector<State::Ptr> mStates;
		std::vector<PendingChange> mPendingList;

		std::map<std::string, std::function<State::Ptr()>> mFactories;

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

template<typename T>
void StateManager::registerState(std::string const& id)
{
	mFactories[id] = [this] ()
	{
		return State::Ptr(new T(*this));
	};
}

#endif // STATEMANAGER_HPP
