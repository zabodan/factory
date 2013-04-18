#pragma once
#include "SourceLocation.h"
#include "LogLevel.h"
#include <string>
#include <memory>


namespace core
{
    class ILogger
    {
    public:

        virtual void write(
            const LogLevel& level,
            const std::string& title,
            const std::string& message,
            const SourceLocation& location) = 0;

        virtual ~ILogger() {}
    };

    typedef std::shared_ptr<ILogger> ILoggerPtr;
}
