#pragma once
#include "ILogger.h"
#include "WorkerThread.h"
#include <boost/bind.hpp>

namespace core
{
    class DeferredLogger : public ILogger
    {
    public:

        explicit DeferredLogger(const ILoggerPtr& logger) : m_targetLogger(logger)
        {
        }

    protected:

        void write(const LogLevel &level, const std::string &message, const SourceLocation &location) override
        {
            m_serviceThread.enqueue(boost::bind(&ILogger::write, m_targetLogger, level, message, location));
        }

        ILoggerPtr m_targetLogger;
        WorkerThread m_serviceThread;
    };


    inline ILoggerPtr CreateDeferredLogger(const ILoggerPtr& logger)
    {
        return std::make_shared<DeferredLogger>(logger);
    }
}
