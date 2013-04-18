#pragma once

namespace core
{
    class SourceLocation
    {
    public:

        SourceLocation(const char* file, const char* func, unsigned int line)
            : m_file(file), m_func(func), m_line(line)
        {
        }

        const char* getFile() const { return m_file; }
        const char* getFunc() const { return m_func; }
        unsigned int getLine() const { return m_line; }

    private:

        const char* m_file;
        const char* m_func;
        unsigned int m_line;
    };

    template <typename Stream>
    Stream& operator<<(Stream& out, const SourceLocation& location)
    {
        out << location.getFile() << ":" << location.getLine() << " in " << location.getFunc();
        return out;
    }
}

#define SOURCE_LOCATION SourceLocation(__FILE__, __FUNCTION__, __LINE__)
