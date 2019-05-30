#pragma once

/*
 This file needs:
 - <assert.h>
*/

#include "SmartPtr.hpp"

namespace ulib {
    template <typename T>
    class SharedPtr
        : public SmartPtr<T> {
    public:
        inline SharedPtr(T* ptr);
        inline SharedPtr(T src);
        inline SharedPtr(const SharedPtr& src);
        ~SharedPtr();

        inline const uint64_t& GetRefCount() const { return *m_refCount; }

    private:
        uint64_t    *m_refCount;

    private:
        struct _BOOL { bool value = false; };
        typedef std::unordered_map<uintptr_t, _BOOL> _HANDELED_HASH;

        inline static _HANDELED_HASH HandeledPtrs() {
            static _HANDELED_HASH s_handeledPtrs;
            return s_handeledPtrs;
        }

    };

    template <typename T>
    inline SharedPtr<T>::SharedPtr(T* ptr)
        : m_refCount(new uint64_t) {
        *m_refCount = 1;
        assert(ptr);
        uintptr_t _address = reinterpret_cast<uintptr_t>(ptr);
        assert(!HandeledPtrs()[_address].value);
        this->m_ptr = ptr;
        HandeledPtrs()[_address].value = true;

    }
    template <typename T>
    inline SharedPtr<T>::SharedPtr(T src)
        : m_refCount(new uint64_t) {
        *m_refCount = 1;
        T *_ptr = new T(src);
        uintptr_t _address = reinterpret_cast<uintptr_t>(_ptr);
        assert(!HandeledPtrs()[_address].value);
        this->m_ptr = _ptr;
        HandeledPtrs()[_address].value = true;
    }
    template <typename T>
    inline SharedPtr<T>::SharedPtr(const SharedPtr& src)
        : m_refCount(&(++(*src.m_refCount))) { this->m_ptr = src.m_ptr; }
    template <typename T>
    SharedPtr<T>::~SharedPtr() {
        (*m_refCount)--;

        if (*m_refCount <= 0) {
            delete this->m_ptr;
            this->m_ptr = nullptr;
            delete m_refCount;
            m_refCount = nullptr;
        }
    }
}
