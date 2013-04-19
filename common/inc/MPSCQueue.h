#pragma once
#include <boost/atomic.hpp>

namespace core
{
    template <typename T>
    struct MPSCQueue
    {
    public:

        MPSCQueue();
        ~MPSCQueue();

        bool enqueue(const T& value);
        bool dequeue(T& result);

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

        // for one producer at a time
        boost::atomic<Node*> m_tail;
        char pad3[cCacheLineSize - sizeof(boost::atomic<Node*>)];
    };


    template <typename T>
    inline MPSCQueue<T>::MPSCQueue()
    {
        m_tail = m_head = new Node(T());
    }

    template <typename T>
    inline MPSCQueue<T>::~MPSCQueue()
    {
        while (m_head != nullptr)
        {
            Node* tmp = m_head;
            m_head = tmp->next;
            delete tmp;
        }
    }

    template <typename T>
    inline bool MPSCQueue<T>::enqueue(const T& value)
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
    inline bool MPSCQueue<T>::dequeue(T& result)
    {
        Node* theFirst = m_head;
        Node* theNext = m_head->next;

        // if queue is nonempty
        if (theNext != nullptr)
        {
            result = std::move(theNext->value);
            m_head = theNext;

            delete theFirst;
            return true;
        }
        return false;
    }
}
