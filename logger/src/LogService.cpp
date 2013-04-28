#include "LogService.h"

using namespace core;


LogService::LogService()
{
}


void LogService::deferredWrite(
    const ILoggerPtr& logger,
    const LogLevel& level,
    const std::string& message,
    const SourceLocation& location)
{
    m_serviceThread.enqueue([=]{
        logger->write(level, message, location);
    });
}
