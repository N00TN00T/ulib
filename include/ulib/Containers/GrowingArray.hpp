#pragma once

namespace ulib {

    template <typename T>
    class GrowingArray {
    public:
        typedef Iterator<GrowingArray<T>, T> Iter;

        inline GrowingArray()
            : m_array(Array<T>(1)), m_length(0) {}
        inline GrowingArray(uint64_t capacity)
            : m_array(Array<T>(capacity)), m_length(0) {}

        inline T& Get(const uint64_t& index) {
            assert(index < m_length);
            return m_array.Get(index);
        }

        inline T& operator[](const uint64_t& index) {
            return Get(index);
        }

        inline void Allocate(uint64_t newCapacity) {
            assert(newCapacity > m_array.GetLength());

            m_array.Resize(newCapacity);
        }

        /* Reallocate memory. Not responsible for freeing memory if length is shrinked */
        inline void SetLength(uint64_t newLength) {
            SecureEnoughLength(newLength);
            m_length = newLength;
        }

        inline const uint64_t& GetLength() const { return m_length; }
        inline const uint64_t& GetCapacity() const { return m_array.GetLength(); }

        inline void Push(T value) {
            SecureEnoughLength(m_length + 1);
            m_array[m_length++] = value;
        }
        inline void Insert(T value, const uint64_t& index) {
            SecureEnoughLength(m_length + 1);
            if (index == m_length) { Push(value); }
            for (uint64_t i = m_length; i > index; i--) {
                m_array[i] = m_array[i - 1];
            }
            m_array[index] = value;
        }

        inline void Pop() {
            assert(m_length > 0);
            m_length--;
        }

        inline void RemoveAt(uint64_t index) {
            assert(index < m_length);
            if (index == m_length - 1) { this->Pop(); return; }

            for (uint64_t i = index; i < m_length - 1; i++) {
                m_array[i] = m_array[i + 1];
            }

            m_length--;
        }

        inline void Clear() {
            this->SetLength(1);
        }

        inline Iter begin() {
            return Iter(*this, 0);
        }
        inline Iter end() {
            return Iter(*this, m_length - 1);
        }

    private:
        inline void SecureEnoughLength(uint64_t targetLength) {
            if (this->GetCapacity() < targetLength) {
                double _ratioCeiled = (int)(((double)targetLength / (double)this->GetCapacity()) + 1);
                this->Allocate(this->GetCapacity() * _ratioCeiled);
            }
        }

    private:
        Array<T> m_array;
        uint64_t m_length;
    };
}
