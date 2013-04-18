#pragma once
#include <boost/atomic.hpp>
#include <boost/thread.hpp>

namespace core
{
    class SpinLock
    {
    public:

        SpinLock() : m_state(Unlocked) {}

        void lock()
        {
            while (m_state.exchange(Locked, boost::memory_order_acquire) == Locked)
            {
                boost::this_thread::sleep_for(boost::chrono::nanoseconds(100));
            }
        }

        void unlock()
        {
            m_state.store(Unlocked, boost::memory_order_release);
        }

    private:
        enum LockState { Locked, Unlocked };
        boost::atomic<LockState> m_state;
    };
}
