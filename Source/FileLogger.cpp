#include "FileLogger.hpp"

FileLogger::FileLogger() : mFile(), mConsole(false), mTimeFormat("[%x][%X]"), mType(FileLogger::LogType::Info)
{
}

bool FileLogger::openLog(std::string const& filename)
{
    mFile.open(filename,std::ios::app);
    return mFile.is_open();
}

bool FileLogger::isLogOpen()
{
    return mFile.is_open();
}

void FileLogger::useConsole(bool use)
{
    mConsole = use;
}

void FileLogger::setTimeFormat(std::string const& timeFormat)
{
    mTimeFormat = timeFormat;
}
