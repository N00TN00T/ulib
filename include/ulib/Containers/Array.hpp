#pragma once

/*
 This file needs:
 - <string.h>
*/

namespace ulib {

    template <typename T>
    class Array {
    public:
        typedef ulib::Iterator<Array<T>, T> Iter;

        inline Array(const uint64_t& length)
            : m_length(length) {
            assert(length > 0);
            m_data = new T[length];
        }

        inline T& Get(const uint64_t& index) {
            assert(index < m_length);
            return m_data[index];
        }

        inline T& operator[](const uint64_t& index) {
            return Get(index);
        }

		inline Array<T> Copy() const {
			Array<T> _cp(m_length);
			memcpy(_cp.m_data, m_data, ToByteSize(m_length));
			return _cp;
		}

        /* Reallocate memory. Not responsible for freeing memory if length is shrinked */
        inline void Resize(uint64_t newLength) {
            //m_data = (T*)realloc(m_data, ToByteSize(newLength));

			T* _newData = new T[newLength];

			uint64_t _cpyLen = newLength > m_length ? m_length : newLength;
			memcpy(_newData, m_data, ToByteSize(_cpyLen));

			delete[] m_data;
			m_data = _newData;

            m_length = newLength;
        }

        inline const uint64_t& GetLength() const { return m_length; }

        inline Iter begin() {
            return Iter(*this, 0);
        }
        inline Iter end() {
            return Iter(*this, m_length - 1);
        }

    private:
        inline size_t ToByteSize(uint64_t count) const { return count * sizeof(T); }

    private:
        uint64_t m_length;
        T *m_data;
    };
}
