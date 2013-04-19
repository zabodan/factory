#define BOOST_TEST_MODULE ConcurQueueTest
#include <boost/test/unit_test.hpp>

#include "MPSCQueue.h"
#include "MPMCQueue.h"


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
