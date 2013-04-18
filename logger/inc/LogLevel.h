#pragma once

namespace core
{
    struct LogLevel
    {
        enum Type
        {
            Trace = 0,
            Debug,
            Info,
            Warning,
            Error,
            Assert
        };

        LogLevel(Type v) : m_value(v) {}
        operator Type() const { return m_value; }

    private:

        Type m_value;
    };

    template <typename Stream>
    Stream& operator<<(Stream& out, const LogLevel& level)
    {
        static const char* c_levelStr[] = { " -T- ", " -D- ", " -I- ", " -W- ", " -E- ", " -A- " };
        out << c_levelStr[level];
        return out;
    }
}
