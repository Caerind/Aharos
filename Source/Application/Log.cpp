#include "Log.hpp"

namespace ah
{

Log::Log() : mFile(), mConsole(true), mType(Log::LogType::Info)
{
    openLog("Assets/Data/log.dat");
}

bool Log::openLog(std::string const& filename)
{
    mFile.open(filename,std::ios::app);
    return mFile.is_open();
}

bool Log::isLogOpen()
{
    return mFile.is_open();
}

void Log::useConsole(bool use)
{
    mConsole = use;
}

} // namespace ah
