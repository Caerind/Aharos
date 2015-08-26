#ifndef AH_LOG_HPP
#define AH_LOG_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Clock.hpp"

namespace ah
{

class Log
{
    public:
        Log();

        bool openLog(std::string const& filename);
        bool isLogOpen();

        enum LogType
        {
            Error,
            Warning,
            Info,
        };

        friend Log& operator<<(Log& log, std::string const& message)
        {
            std::stringstream ss;
            ss << getTime(log.mTimeFormat);
            switch (log.mType)
            {
                case Log::Error:
                    ss << "[ERROR] : ";
                    break;

                case Log::Warning:
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

            log.mType = Log::Info;

            return log;
        }

        friend Log& operator<<(Log& log, LogType type)
        {
            log.mType = type;
            return log;
        }

        void log(std::string const& message, LogType type = Log::Info);

        void useConsole(bool use);
        void setTimeFormat(std::string const& timeFormat);

    private:
        std::ofstream mFile;
        bool mConsole;
        std::string mTimeFormat;
        LogType mType;
};

}

#endif // AH_LOG_HPP
