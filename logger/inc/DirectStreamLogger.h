#pragma once
#include "ILogger.h"
#include "SpinLock.h"

namespace core
{
    template <class Stream>
    class DirectStreamLogger : public ILogger
    {
    public:

        DirectStreamLogger(Stream& out) : m_stream(out)
        {
        }

    protected:

        void write(const LogLevel &level, const std::string &title, const std::string &message, const SourceLocation &location) override
        {
            boost::lock_guard guard(m_lock);
            m_stream << level << title << ": \"" << message << "\" -- " << location << std::endl;
        }

        Stream& m_stream;
        SpinLock m_lock;
    };
}
