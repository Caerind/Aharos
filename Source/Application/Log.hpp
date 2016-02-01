#ifndef AH_LOG_HPP
#define AH_LOG_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>

#include "../Helper/Time.hpp"

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
            ss << lp::getTime("[%x][%X]");
            switch (log.mType)
            {
                case Log::LogType::Error:
                    ss << "[ERROR] : ";
                    break;

                case Log::LogType::Warning:
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

            log.mType = Log::LogType::Info;

            return log;
        }

        friend Log& operator<<(Log& log, LogType type)
        {
            log.mType = type;
            return log;
        }

        void useConsole(bool use);

    protected:
        std::ofstream mFile;
        bool mConsole;
        LogType mType;
};

} // namespace ah

#endif // AH_LOG_HPP
