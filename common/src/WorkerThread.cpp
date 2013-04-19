#include "WorkerThread.h"
#include <boost/bind.hpp>

using namespace core;

WorkerThread::WorkerThread()
{
    m_stopRequested.store(false, boost::memory_order_release);
    m_thread.reset(new boost::thread(boost::bind(&WorkerThread::run, this)));
}

WorkerThread::~WorkerThread()
{
    m_stopRequested.store(true, boost::memory_order_release);
    m_thread->join();
}

bool WorkerThread::enqueue(const Task& task)
{
    return m_tasks.push(task);
}

void WorkerThread::run()
{
    Task task;
    while (m_stopRequested.exchange(false, boost::memory_order_acquire) == false)
    {
        for (size_t i = 0; i < 20; ++i)
        {
            if (m_tasks.pop(task))
            {
                task();
            }
        }

        boost::this_thread::yield();
    }

    while (m_tasks.pop(task))
    {
        task();
    }
}
