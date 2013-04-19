#pragma once
#include "MPSCQueue.h"
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/atomic.hpp>
#include <memory>

namespace core
{
    class WorkerThread
    {
    public:

        typedef boost::function<void()> Task;

        WorkerThread();
        ~WorkerThread();

        bool enqueue(const Task& task);

    protected:

        void run();

        std::unique_ptr<boost::thread> m_thread;
        boost::atomic_bool m_stopRequested;
        MPSCQueue<Task> m_tasks;
    };
}
