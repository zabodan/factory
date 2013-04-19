#pragma once

namespace core
{
    class LogService
    {
    public:
        static LogService& instance();

    private:
        LogService();
    };
}
