#pragma once

#include "ulib/Containers/Array.hpp"

namespace ulib {
    class Bitset {
    public:
        struct _INT64 {
            int64_t value = 0ULL;
			_INT64() : value(0ULL) {}
			_INT64(int64_t v) : value(v) {}
        };
        inline Bitset() : m_bitsets(Array<_INT64>(1)) {}
		inline Bitset(int64_t firstBits) : m_bitsets(Array<_INT64>(1)) {
			m_bitsets[0] = firstBits;
		}
		inline Bitset(const Bitset& src)
		 : m_bitsets(Array<_INT64>(src.m_bitsets.GetLength())) {
			m_bitsets = src.m_bitsets.Copy();
		}

        inline void SetBit(uint8_t bit, bool value = true) {
			uint8_t _index = bit / 64;

			uint8_t _offsetBit = bit - _index * 64;
            if (m_bitsets.GetLength() <= _index) { m_bitsets.Resize(_index + 1); }

            if (value) {
                m_bitsets[_index].value |= (1ULL << _offsetBit);
            } else {
                m_bitsets[_index].value &= ~(1ULL << _offsetBit);
            }
        }

        inline bool GetBit(uint8_t bit) {
			uint8_t _index = bit / 64;
            if (_index >= m_bitsets.GetLength()) return false;
			uint8_t _offsetBit = bit - _index * 64;
            return (m_bitsets[_index].value & (1ULL << _offsetBit)) != 0;
        }

    private:
        Array<_INT64> m_bitsets;
    };
}
