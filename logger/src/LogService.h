#pragma once
#include "ILogger.h"
#include "WorkerThread.h"

namespace core
{
    class LogService
    {
    public:
        static LogService& instance();

        void deferredWrite(
            const ILoggerPtr& logger,
            const LogLevel& level,
            const std::string& title,
            const std::string& message,
            const SourceLocation& location);

    private:
        LogService();

    protected:
        WorkerThread m_serviceThread;
    };
}
