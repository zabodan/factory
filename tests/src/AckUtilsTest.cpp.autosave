#define BOOST_TEST_MODULE BasicAckTest
#include <boost/test/unit_test.hpp>

#include "AckUtils.h"


BOOST_AUTO_TEST_CASE(MoreRecentSeqNumTest)
{
    BOOST_CHECK(core::IsMoreRecentSeqNum(1, 0));
    BOOST_CHECK(!core::IsMoreRecentSeqNum(0, 0));
    BOOST_CHECK(!core::IsMoreRecentSeqNum(0, 1));

    BOOST_CHECK(core::IsMoreRecentSeqNum(4, 2));
    BOOST_CHECK(!core::IsMoreRecentSeqNum(2, 5));
    BOOST_CHECK(!core::IsMoreRecentSeqNum(3, 3));

    BOOST_CHECK(core::IsMoreRecentSeqNum(2, 65530));
    BOOST_CHECK(!core::IsMoreRecentSeqNum(65530, 5));
}


BOOST_AUTO_TEST_CASE(TestAck33)
{
    core::ack33_t ack33; // templated case, one of { 9, 17, 33, 65 }
    ack33.updateForSeqNum(1); BOOST_CHECK(ack33.ackBits() == 0x0001 && ack33.lastSeqNum() == 1); // bits = 00000001, ack = 1
    ack33.updateForSeqNum(3); BOOST_CHECK(ack33.ackBits() == 0x0006 && ack33.lastSeqNum() == 3); // bits = 00000110, ack = 3
    ack33.updateForSeqNum(2); BOOST_CHECK(ack33.ackBits() == 0x0007 && ack33.lastSeqNum() == 3); // bits = 00000111, ack = 3
    ack33.updateForSeqNum(7); BOOST_CHECK(ack33.ackBits() == 0x0078 && ack33.lastSeqNum() == 7); // bits = 01111000, ack = 7
    ack33.updateForSeqNum(6); BOOST_CHECK(ack33.ackBits() == 0x0079 && ack33.lastSeqNum() == 7); // bits = 01111001, ack = 7

    std::vector<uint16_t> packets;
    ack33.forEachAckedSeqNum([&](uint16_t seqNum){
        packets.push_back(seqNum);
    });

    const uint16_t expected[] = { 7, 6, 3, 2, 1, 0 };
    BOOST_CHECK(packets.size() == sizeof(expected) / sizeof(uint16_t));
    BOOST_CHECK(std::equal(packets.begin(), packets.end(), expected));
}


BOOST_AUTO_TEST_CASE(TestAck49)
{
    core::ack49_t ack49; // special case
    ack49.updateForSeqNum(1); BOOST_CHECK(ack49 == 0x00010001); // bits = 00000001, ack = 1
    ack49.updateForSeqNum(3); BOOST_CHECK(ack49 == 0x00060003); // bits = 00000110, ack = 3
    ack49.updateForSeqNum(2); BOOST_CHECK(ack49 == 0x00070003); // bits = 00000111, ack = 3
    ack49.updateForSeqNum(7); BOOST_CHECK(ack49 == 0x00780007); // bits = 01111000, ack = 7
    ack49.updateForSeqNum(6); BOOST_CHECK(ack49 == 0x00790007); // bits = 01111001, ack = 7

    std::vector<uint16_t> packets;
    ack49.forEachAckedSeqNum([&](uint16_t seqNum){
        packets.push_back(seqNum);
    });

    const uint16_t expected[] = { 7, 6, 3, 2, 1, 0 };
    BOOST_CHECK(packets.size() == sizeof(expected) / sizeof(uint16_t));
    BOOST_CHECK(std::equal(packets.begin(), packets.end(), expected));
}
