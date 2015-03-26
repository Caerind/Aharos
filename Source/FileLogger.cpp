#include "FileLogger.hpp"

FileLogger FileLogger::gInstance;
bool FileLogger::gInitialised;

FileLogger* FileLogger::instance()
{
    return gInitialised ? &gInstance : nullptr;
}

bool FileLogger::open(std::string const& filename)
{
    if (instance() != nullptr)
    {
        instance()->mFile.open(filename,std::ios::app);
        return instance()->mFile.is_open();
    }
    return false;
}

bool FileLogger::isOpen()
{
    if (instance() != nullptr)
    {
        return instance()->mFile.is_open();
    }
    return false;
}

void FileLogger::write(FileLogger::LogType type, std::string const& message)
{
    if (instance() != nullptr)
    {
        std::stringstream ss;
        ss << getTime(instance()->mTimeFormat);
        switch (type)
        {
            case LogType::Error:
                ss << "[ERROR] : ";
                break;

            case LogType::Warning:
                ss << "[WARNING] : ";
                break;

            default:
                ss << "[INFO] : ";
        }
        ss << message;

        if (instance()->mConsole)
            std::cout << ss.str() << std::endl;
        if (instance()->mFile.is_open())
            instance()->mFile << ss.str() << std::endl;
    }
}

void FileLogger::write(std::string const& message)
{
    FileLogger::write(LogType::Info,message);
}

void FileLogger::useConsole(bool use)
{
    if (instance() != nullptr)
    {
        instance()->mConsole = true;
    }
}

bool FileLogger::usingConsole()
{
    if (instance() != nullptr)
    {
        return instance()->mConsole;
    }
    return false;
}

void FileLogger::setTimeFormat(std::string const& timeFormat)
{
    if (instance() != nullptr)
    {
        instance()->mTimeFormat = timeFormat;
    }
}

std::string FileLogger::getTimeFormat()
{
    if (instance() != nullptr)
    {
        return instance()->mTimeFormat;
    }
    return "";
}

std::string FileLogger::getTime(std::string timeFormat)
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,timeFormat.c_str(),timeinfo);
    return std::string(buffer);
}

FileLogger::FileLogger()
{
    gInitialised = true;
    mConsole = false;
    mTimeFormat = "[%x][%X]";
}

FileLogger::~FileLogger()
{
    gInitialised = false;
}
