#pragma once
#include "ILogger.h"


class TestLogger : public core::ILogger
{
public:

    TestLogger()
    {
        //m_logger = std::make_shared<core::StreamLogger<std::ostringstream>>(m_stream);
    }

    const std::string& getMessage() const
    {
        //return m_stream.str();
        return m_message;
    }

protected:

    //std::ostringstream m_stream;
    //core::ILoggerPtr m_logger;
    std::string m_message;

    void write(const core::LogLevel& /*level*/, const std::string& message, const core::SourceLocation& /*location*/)
    {
        //m_stream.str("");
        //m_logger->write(level, message, location);
        m_message = message;
    }
};
