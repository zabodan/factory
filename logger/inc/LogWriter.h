#pragma once
#include "ILogger.h"
#include <boost/format.hpp>
#include <boost/noncopyable.hpp>

namespace core
{
    class LogWriter : private boost::noncopyable
    {
    public:

        LogWriter(const ILoggerPtr& logger, const LogLevel& level, const std::string& message, const SourceLocation& location)
            : m_logger(logger), m_level(level), m_message(message), m_location(location)
        {
            disableFormatExceptions();
        }

        LogWriter(const ILoggerPtr& logger, const LogLevel& level, std::string&& message, const SourceLocation& location)
            : m_logger(logger), m_level(level), m_message(std::move(message)), m_location(location)
        {
            disableFormatExceptions();
        }

        ~LogWriter()
        {
            if (m_logger)
            {
                m_logger->write(m_level, m_message.str(), m_location);
            }
        }

        template <typename T>
        LogWriter& operator<<(const T& value)
        {
            m_message % value;
            return *this;
        }

    protected:

        void disableFormatExceptions()
        {
            m_message.exceptions(boost::io::all_error_bits ^ (boost::io::too_many_args_bit | boost::io::too_few_args_bit));
        }

        const ILoggerPtr m_logger;
        const LogLevel m_level;
        const SourceLocation m_location;
        boost::format m_message;
    };
}


#define LogTrace(logger, message) core::LogWriter((logger), core::LogLevel::Trace, (message), SOURCE_LOCATION)
#define LogDebug(logger, message) core::LogWriter((logger), core::LogLevel::Debug, (message), SOURCE_LOCATION)
#define LogInfo(logger, message) core::LogWriter((logger), core::LogLevel::Info, (message), SOURCE_LOCATION)
#define LogWarning(logger, message) core::LogWriter((logger), core::LogLevel::Warning, (message), SOURCE_LOCATION)
#define LogError(logger, message) core::LogWriter((logger), core::LogLevel::Error, (message), SOURCE_LOCATION)
#define LogAssert(logger, message) core::LogWriter((logger), core::LogLevel::Assert, (message), SOURCE_LOCATION)
