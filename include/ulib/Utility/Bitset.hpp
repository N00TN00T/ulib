#pragma once

#include "ulib/Containers/Array.hpp"

namespace ulib {
    class Bitset {
    public:
        struct _INT64 {
            int64_t value = 0ULL;
        };
        inline Bitset() : m_bitsets(Array<_INT64>(1)) {}

        inline void SetBit(uint32_t bit, bool value = true) {
            uint32_t _index = bit / 64;

            uint32_t _offsetBit = bit - _index * 64;
            if (m_bitsets.GetLength() <= _index) { m_bitsets.Resize(_index + 1); }

            if (value) {
                m_bitsets[_index].value |= (1ULL << _offsetBit);
            } else {
                m_bitsets[_index].value &= ~(1ULL << _offsetBit);
            }
        }

        inline bool GetBit(uint32_t bit) {
            uint32_t _index = bit / 64;
            if (_index >= m_bitsets.GetLength()) return false;
            uint32_t _offsetBit = bit - _index * 64;
            return (m_bitsets[_index].value & (1ULL << _offsetBit)) != 0;
        }

    private:
        Array<_INT64> m_bitsets;
    };
}
