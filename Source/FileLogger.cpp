#include "FileLogger.hpp"

FileLogger::FileLogger(std::string const& filename) : mFile(), mConsole(false), mTimeFormat("[%x][%X]"), mType(FileLogger::LogType::Info)
{
    mFile.open(filename,std::ios::app);
    #ifdef AH_DEBUG
    mConsole = true;
    #endif // AH_DEBUG
}

void FileLogger::useConsole(bool use)
{
    mConsole = use;
}

void FileLogger::setTimeFormat(std::string const& timeFormat)
{
    mTimeFormat = timeFormat;
}
