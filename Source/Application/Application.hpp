#ifndef AH_APPLICATION_HPP
#define AH_APPLICATION_HPP

#include "StateManager.hpp"
#include "Window.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "LangManager.hpp"
#include "Log.hpp"
#include "../Helper/KeyBinding.hpp"

namespace ah
{

class Application
{
    public:
        static Application& instance();

        static void run();

        static StateManager& getStates();
        static Window& getWindow();
        static AudioManager& getAudio();
        static ResourceManager& getResources();
        static LangManager& getLang();
        static Log& getLog();
        static lp::KeyBinding& getBinding();

    private:
        Application();
        ~Application();

        static Application mInstance;

        StateManager mStates;
        Window mWindow;
        AudioManager mAudio;
        ResourceManager mResources;
        LangManager mLang;
        Log mLog;
        lp::KeyBinding mBinding;
};

} // namespace ah

#define ah_Log ah::Application::getLog()

#endif // AH_APPLICATION_HPP
