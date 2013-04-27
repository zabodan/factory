#pragma once
#include "ILogger.h"
#include <boost/format.hpp>
#include <boost/noncopyable.hpp>

namespace core
{
    class LogWriter : private boost::noncopyable
    {
    public:

        LogWriter(
            const ILoggerPtr& logger,
            const LogLevel& level,
            const std::string& title,
            const std::string& message,
            const SourceLocation& location)
          : m_logger(logger),
            m_level(level),
            m_title(title),
            m_message(message),
            m_location(location)
        {
            m_message.exceptions(boost::io::all_error_bits ^ (boost::io::too_many_args_bit | boost::io::too_few_args_bit));
        }

        ~LogWriter()
        {
            if (m_logger)
            {
                m_logger->write(m_level, m_title, m_message.str(), m_location);
            }
        }

        template <typename T>
        LogWriter& operator<<(const T& value)
        {
            m_message % value;
            return *this;
        }

    protected:

        const ILoggerPtr& m_logger;
        const LogLevel& m_level;
        const SourceLocation& m_location;
        const std::string& m_title;
        boost::format m_message;
    };
}


#define LogTrace(logger, title, message) core::LogWriter((logger), core::LogLevel::Trace, (title), (message), SOURCE_LOCATION)
#define LogDebug(logger, title, message) core::LogWriter((logger), core::LogLevel::Debug, (title), (message), SOURCE_LOCATION)
#define LogInfo(logger, title, message) core::LogWriter((logger), core::LogLevel::Info, (title), (message), SOURCE_LOCATION)
#define LogWarning(logger, title, message) core::LogWriter((logger), core::LogLevel::Warning, (title), (message), SOURCE_LOCATION)
#define LogError(logger, title, message) core::LogWriter((logger), core::LogLevel::Error, (title), (message), SOURCE_LOCATION)
#define LogAssert(logger, title, message) core::LogWriter((logger), core::LogLevel::Assert, (title), (message), SOURCE_LOCATION)
