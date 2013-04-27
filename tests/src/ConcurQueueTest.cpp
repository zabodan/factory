#define BOOST_TEST_MODULE ConcurQueueTest
#include <boost/test/unit_test.hpp>

#include "MPSCQueue.h"
#include "MPMCQueue.h"
#include "Singleton.h"
#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>
#include <iostream>

template <template <class> class Queue>
static void TestQueue()
{
    Queue<int> queue;
    int tmp = 0;
    BOOST_CHECK(!queue.pop(tmp));
    BOOST_CHECK(queue.push(1));
    BOOST_CHECK(queue.push(2));
    BOOST_CHECK(queue.pop(tmp) && tmp == 1);
    BOOST_CHECK(queue.push(3));
    BOOST_CHECK(queue.pop(tmp) && tmp == 2);
    BOOST_CHECK(queue.pop(tmp) && tmp == 3);
    BOOST_CHECK(!queue.pop(tmp));
    BOOST_CHECK(queue.push(4));
    BOOST_CHECK(queue.pop(tmp) && tmp == 4);
}


BOOST_AUTO_TEST_CASE(ConcurrentQueuesWork)
{
    TestQueue<core::MPSCQueue>();
    TestQueue<core::MPMCQueue>();
}

boost::atomic_int ctrCount(0);
boost::atomic_int dtrCount(0);

struct A : public core::SingletonBase<A>
{
    A() { std::cout << "A" << std::endl; }
    ~A() { std::cout << "~A" << std::endl; }
};

struct B : public core::SingletonBase<B>
{
    B() { std::cout << "B" << std::endl; }
    ~B() { std::cout << "~B" << std::endl; }
private:
    core::DependsOn<A> m_ra;
};

struct C : public core::SingletonBase<C>
{
    C() { std::cout << "C" << std::endl; }
    ~C() { std::cout << "~C" << std::endl;  }
private:
    core::DependsOn<B> m_rb;
};

struct D : public core::SingletonBase<D>
{
    D() { std::cout << "D" << std::endl; }
    ~D() { std::cout << "~D" << std::endl;  }
};


struct S : public core::SingletonBase<S>
{
    S() : i(0) { ++ctrCount; std::cout << "S" << std::endl; }
    ~S() { ++dtrCount; std::cout << "~S" << std::endl; }
    boost::atomic_int i;
private:
    core::DependsOn<D> m_rd;
    core::DependsOn<C> m_rc;
};

BOOST_AUTO_TEST_CASE(SingletonMT)
{
    boost::thread_group grp;
    for (size_t i = 0; i < 8; ++i)
    {
        grp.create_thread([]{
           ++S::instance().i;
        });
    }

    grp.join_all();
    BOOST_CHECK(ctrCount == 1);
    BOOST_CHECK(dtrCount == 0);
    BOOST_CHECK(S::instance().i == 8);
}
