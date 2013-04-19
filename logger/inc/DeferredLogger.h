#pragma once
#include "ILogger.h"

namespace core
{
    class DeferredLogger : public ILogger
    {
    public:

        explicit DeferredLogger(const ILoggerPtr& logger) : m_logger(logger)
        {
        }

    protected:

        void write(const LogLevel &level, const std::string &title, const std::string &message, const SourceLocation &location) override;

        ILoggerPtr m_logger;
    };
}
