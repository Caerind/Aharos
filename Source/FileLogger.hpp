#ifndef AH_FILELOGGER_HPP
#define AH_FILELOGGER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Clock.hpp"

namespace ah
{

class FileLogger
{
    public:
        FileLogger();

        bool openLog(std::string const& filename);
        bool isLogOpen();

        enum LogType
        {
            Error,
            Warning,
            Info,
        };

        friend FileLogger& operator<<(FileLogger& log, std::string const& message)
        {
            std::stringstream ss;
            ss << getTime(log.mTimeFormat);
            switch (log.mType)
            {
                case FileLogger::LogType::Error:
                    ss << "[ERROR] : ";
                    break;

                case FileLogger::LogType::Warning:
                    ss << "[WARNING] : ";
                    break;

                default:
                    ss << "[INFO] : ";
            }
            ss << message;
            std::string str = ss.str();

            if (log.mConsole)
                std::cout << str << std::endl;

            if (log.mFile.is_open())
                log.mFile << str << std::endl;

            log.mType = FileLogger::LogType::Info;

            return log;
        }

        friend FileLogger& operator<<(FileLogger& log, LogType type)
        {
            log.mType = type;
            return log;
        }

    protected:
        void useConsole(bool use);
        void setTimeFormat(std::string const& timeFormat);

    private:
        std::ofstream mFile;
        bool mConsole;
        std::string mTimeFormat;
        LogType mType;
};

}

#endif // AH_FILELOGGER_HPP
