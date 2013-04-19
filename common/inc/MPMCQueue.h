#pragma once
#include <boost/atomic.hpp>
#include <boost/thread.hpp>

namespace core
{
    template <typename T>
    class MPMCQueue
    {
    public:

        MPMCQueue();
        ~MPMCQueue();

        bool push(const T& value);
        bool pop(T& result);

    private:

        struct Node
        {
            explicit Node(const T& v) : value(v), next(nullptr) {}

            T value;
            boost::atomic<Node*> next;
        };

        // cache line size on modern x86 processors (in bytes)
        static const size_t cCacheLineSize = 64;

        char pad0[cCacheLineSize];

        // for one consumer at a time
        Node* m_head;
        char pad1[cCacheLineSize - sizeof(Node*)];

        // shared among consumers
        boost::atomic<bool> m_consumerLock;
        char pad2[cCacheLineSize - sizeof(boost::atomic<bool>)];

        // for one producer at a time
        boost::atomic<Node*> m_tail;
        char pad3[cCacheLineSize - sizeof(boost::atomic<Node*>)];
    };


    template <typename T>
    inline MPMCQueue<T>::MPMCQueue()
    {
        m_tail = m_head = new Node(T());
        m_consumerLock = false;
    }

    template <typename T>
    inline MPMCQueue<T>::~MPMCQueue()
    {
        while (m_head != nullptr)
        {
            Node* tmp = m_head;
            m_head = tmp->next;
            delete tmp;
        }
    }

    template <typename T>
    inline bool MPMCQueue<T>::push(const T& value)
    {
        Node* tmp = new (std::nothrow) Node(value);
        if (tmp)
        {
            Node* old = m_tail.exchange(tmp, boost::memory_order_acq_rel);
            old->next = tmp;
            return true;
        }

        return false;
    }

    template <typename T>
    inline bool MPMCQueue<T>::pop(T& result)
    {
        while (m_consumerLock.exchange(true, boost::memory_order_acquire))
        {
            boost::this_thread::sleep_for(boost::chrono::nanoseconds(100));
        }

        Node* theFirst = m_head;
        Node* theNext = m_head->next;

        // if queue is nonempty
        if (theNext != nullptr)
        {
            result = std::move(theNext->value);
            m_head = theNext;
            m_consumerLock.store(false, boost::memory_order_release);

            delete theFirst;
            return true;
        }

        m_consumerLock.store(false, boost::memory_order_release);
        return false;
    }

}
