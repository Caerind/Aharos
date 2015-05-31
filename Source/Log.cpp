#include "Log.hpp"

namespace ah
{

Log::Log() : mFile(), mConsole(false), mTimeFormat("[%x][%X]"), mType(Log::Info)
{
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

void Log::setTimeFormat(std::string const& timeFormat)
{
    mTimeFormat = timeFormat;
}

}
