#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <functional>
#include <map>
#include <vector>

#include "State.hpp"

class Application;

class StateManager : public sf::Drawable
{
    public:
		StateManager(Application& app);

		template<typename T>
		void registerState(std::string const& id);

		void update(sf::Time dt);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void pushState(std::string const& id);
		void popState();
		void clearStates();

		bool isEmpty() const;
		std::size_t getStatesCount() const;
		std::string getActiveStateType() const;
		std::string getLastActiveStateType() const;

		void applyPendingChanges();

		Application& getApplication();

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
        Application& mApplication;

		State::Ptr createState(std::string const& id);

		std::string mLastActiveStateType;

		std::vector<State::Ptr> mStates;
		std::vector<PendingChange> mPendingList;

		std::map<std::string, std::function<State::Ptr()>> mFactories;
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
