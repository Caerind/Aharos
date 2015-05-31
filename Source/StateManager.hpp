#ifndef AH_STATEMANAGER_HPP
#define AH_STATEMANAGER_HPP

#include <functional>
#include <map>
#include <vector>

#include "State.hpp"

namespace ah
{

class Application;

class StateManager : public sf::Drawable
{
    public:
		StateManager(Application& app);

		template<typename T>
		void registerState(std::string const& id);

        void handleEvent(sf::Event const& event);
		void update(sf::Time dt);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void pushState(std::string const& id);
		void popState();
		void clearStates();

		bool empty() const;
		std::size_t size() const;
		std::string getActiveStateType() const;
		std::string getLastActiveStateType() const;

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

		void applyPendingChanges();
		State::Ptr createState(std::string const& id);

	private:
        Application& mApplication;

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

}

#endif // AH_STATEMANAGER_HPP
