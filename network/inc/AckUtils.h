#pragma once
#include <cstdint>
#include <cassert>


namespace core
{

    // Tells whether n1 is more recent sequence number than n2
    inline bool IsMoreRecentSeqNum(uint16_t n1, uint16_t n2)
    {
        static const uint16_t mid = std::numeric_limits<uint16_t>::max() / 2;

        // Full check without overflows is: (n1 > n2 && n1 - n2 < mid) || (n1 < n2 && n2 - n1 > mid),
        // but if we do use integer overflow with operation-, it can be simplified.
        return n1 == n2 ? false : uint16_t(n1 - n2) < mid;
    }


    template <class T, class Enable>
    class basic_ack_impl;

    template <class T, class = typename std::enable_if<std::is_integral<T>::value>::type>
    class basic_ack_impl {};

#pragma pack(push, 1)
    
    template <class BitsType>    
    class basic_ack : public basic_ack_impl<BitsType>
    {
    public:

        // default ctr, zero means packet 0 was acked
        basic_ack() : m_lastSeqNum(0), m_ackBits(0) {}

        // get most recent seqNum from ack
        uint16_t lastSeqNum() const { return m_lastSeqNum; }
        BitsType ackBits() const { return m_ackBits; }
        
        // acknowledge seqNum, update ack and ackBits
        void updateForSeqNum(uint16_t seqNum);

        // call func for each acknowledged seqNum
        template <class Fn>
        void forEachAckedSeqNum(Fn& func) const;

    private:

        static const int cMaxDelta = sizeof(BitsType) * 8;

        BitsType bitFromDelta(uint16_t delta) const
        {
            assert(delta < cMaxDelta);
            return BitsType(1) << delta;
        }

        uint16_t m_lastSeqNum;
        BitsType m_ackBits;
    };

#pragma pack(pop)


    template <class BitsType>
    inline void basic_ack<BitsType>::updateForSeqNum(uint16_t seqNum)
    {
        if (m_lastSeqNum == seqNum)
            return;

        if (IsMoreRecentSeqNum(seqNum, m_lastSeqNum))
        {
            // delta is how many packets we are missing between currAck (latest acknowledged) and seqNum
            uint16_t delta = seqNum - m_lastSeqNum;

            if (delta <= cMaxDelta)
            {
                // shift ackBits, update ack, and don't forget old ack's bit
                m_ackBits = bitFromDelta(delta - 1) | (m_ackBits << delta);
            }
            else
            {
                // ack = seqNum, ackBits all zero
                m_ackBits = 0;
            }
            m_lastSeqNum = seqNum;
        }
        else
        {
            // delta is how many packets were after seqNum
            uint16_t delta = m_lastSeqNum - seqNum;
            if (delta <= cMaxDelta)
            {
                m_ackBits |= bitFromDelta(delta - 1);
            }
        }
    }


    template <class BitsType> template <class Fn>
    inline void basic_ack<BitsType>::forEachAckedSeqNum(Fn& func) const
    {
        func(m_lastSeqNum);
        for (uint16_t delta = 0; delta < cMaxDelta; ++delta)
        {
            uint64_t bit = bitFromDelta(delta);
            if ((m_ackBits & bit) == bit)
            {
                func(m_lastSeqNum - delta - 1);
            }
        }
    }


    typedef basic_ack<uint8_t>  ack9_t;
    typedef basic_ack<uint16_t> ack17_t;
    typedef basic_ack<uint32_t> ack33_t;
    typedef basic_ack<uint64_t> ack65_t;

    // special case
    struct ack49_t
    {
        // default ctr, zero means packet 0 was acked
        ack49_t() : m_data(0) {}

        // acknowledge seqNum, update ack and ackBits
        void updateForSeqNum(uint16_t seqNum);

        // get current value (for testing)
        operator uint64_t() const { return m_data; }
        
        // get most recent seqNum from ack
        uint16_t lastSeqNum() const { return m_data & 0xffff; }
        
        // call func for each acknowledged seqNum
        template <class Fn>
        void forEachAckedSeqNum(Fn& func) const;

    private:

        uint64_t bitFromDelta(uint16_t delta) const
        {
            assert(delta < 48);
            return uint64_t(0x10000) << delta;
        }

        // [ackBits:48][seqNum:16]
        uint64_t m_data;
    };


    inline void ack49_t::updateForSeqNum(uint16_t seqNum)
    {
        uint16_t currAck = lastSeqNum();
        if (currAck == seqNum)
            return;

        if (IsMoreRecentSeqNum(seqNum, currAck))
        {
            // delta is how many packets we are missing between currAck (latest acknowledged) and seqNum
            uint16_t delta = seqNum - currAck;

            if (delta <= 48)
            {
                // shift ackBits, update ack, and don't forget old ack's bit
                m_data = seqNum | bitFromDelta(delta - 1) | ((m_data << delta) & ~uint64_t(0xffff));
            }
            else
            {
                // ack = seqNum, ackBits all zero
                m_data = seqNum;
            }
        }
        else
        {
            // delta is how many packets were after seqNum
            uint16_t delta = currAck - seqNum;
            if (delta <= 48)
            {
                m_data |= bitFromDelta(delta - 1);
            }
        }
    }


    template <class Fn>
    inline void ack49_t::forEachAckedSeqNum(Fn& func) const
    {
        uint16_t currSeqNum = lastSeqNum();
        
        func(currSeqNum);
        for (uint16_t delta = 1; delta <= 48; ++delta)
        {
            uint64_t bit = bitFromDelta(delta - 1);
            if ((m_data & bit) == bit)
            {
                func(currSeqNum - delta);
            }
        }
    }
}
