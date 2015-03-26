#ifndef FILELOGGER_HPP
#define FILELOGGER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

class FileLogger
{
    public:
        static FileLogger* instance();

        static bool open(std::string const& filename);
        static bool isOpen();

        enum LogType
        {
            Error,
            Warning,
            Info,
        };

        static void write(LogType type, std::string const& message);
        static void write(std::string const& message);

        static void useConsole(bool use);
        static bool usingConsole();

        static void setTimeFormat(std::string const& timeFormat);
        static std::string getTimeFormat();

        static std::string getTime(std::string timeFormat);

    private:
        FileLogger();
        ~FileLogger();

        static FileLogger gInstance;
        static bool gInitialised;

        std::ofstream mFile;
        bool mConsole;
        std::string mTimeFormat;
};

#endif // FILELOGGER_HPP
