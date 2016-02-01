#ifndef LP_PARALLELTASK_HPP
#define LP_PARALLELTASK_HPP


#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Clock.hpp>

namespace lp
{

class ParallelTask
{
	public:
        ParallelTask();

		void				execute();
		bool				isFinished();
		float				getCompletion();

    protected:
		void				runTask();

	private:
		sf::Thread			mThread;
		bool				mFinished;
		sf::Clock			mElapsedTime;
		sf::Mutex			mMutex;
};

} // namespace lp

#endif // LP_PARALLELTASK_HPP
