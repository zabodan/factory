#pragma once
#include "ILogger.h"
#include "Singleton.h"
#include "WorkerThread.h"

namespace core
{
    class LogService : public SingletonBase<LogService>
    {
    public:

        void deferredWrite(
            const ILoggerPtr& logger,
            const LogLevel& level,
            const std::string& message,
            const SourceLocation& location);

    protected:

        WorkerThread m_serviceThread;

    private:

        friend class SingletonBase<LogService>;
        LogService();
    };
}
