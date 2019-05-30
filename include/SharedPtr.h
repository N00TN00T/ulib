#pragma once

namespace ulib {
    template <typename T>
    class SharedPtr {
    public:
        inline SharedPtr(T* ptr)
            : m_refCount(new uint64_t), m_ptr(ptr) {
            *m_refCount = 1;
        }
        inline SharedPtr(const SharedPtr& src)
            : m_refCount(&(++(*src.m_refCount))), m_ptr(src.m_ptr) { }
        ~SharedPtr() {
            (*m_refCount)--;

            if (*m_refCount <= 0) {
                delete m_ptr;
                m_ptr = nullptr;
                delete m_refCount;
                m_refCount = nullptr;
            }
        }

        inline const uint64_t& ref_count() const { return *m_refCount; }

        inline T* get() const { return m_ptr; }

        inline T* operator->() const {
            return this->get();
        }

        inline T& operator*() {
            return *this->get();
        }

    private:
        uint64_t    *m_refCount;
        T*          m_ptr;

    public:
        inline static SharedPtr make(T* ptr) {
            return SharedPtr(ptr);
        }
        inline static SharedPtr make(const T& ptr) {
            return SharedPtr(new T(ptr));
        }
    };
}
