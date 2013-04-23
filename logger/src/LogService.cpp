#include "LogService.h"

using namespace core;

LogService::LogService()
{
}


LogService& LogService::instance()
{
    static LogService service;
    return service;
}


void LogService::deferredWrite(
    const ILoggerPtr& logger,
    const LogLevel& level,
    const std::string& title,
    const std::string& message,
    const SourceLocation& location)
{
    m_serviceThread.enqueue([=]{
        logger->write(level, title, message, location);
    });
}
