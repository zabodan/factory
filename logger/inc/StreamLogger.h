#pragma once
#include "ILogger.h"
#include "SpinLock.h"
#include <boost/ref.hpp>

namespace core
{
    template <class Stream>
    class StreamLogger : public ILogger
    {
    public:

        explicit StreamLogger(Stream& out) : m_stream(out)
        {
        }

    protected:

        void write(const LogLevel &level, const std::string &title, const std::string &message, const SourceLocation &location) override
        {
            boost::lock_guard<SpinLock> guard(m_lock);
            m_stream.get() << level << title << ": \"" << message << "\" -- " << location << std::endl;
        }

        typedef boost::reference_wrapper<Stream> StreamRef;

        StreamRef m_stream;
        SpinLock m_lock;
    };


    template <class Stream>
    inline ILoggerPtr CreateStreamLogger(Stream& out)
    {
        return ILoggerPtr(new StreamLogger<Stream>(out));
    }
}
