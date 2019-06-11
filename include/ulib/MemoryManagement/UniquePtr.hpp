#pragma once

/*
 This file needs:
 - <assert.h>
*/

#include "SmartPtr.hpp"

namespace ulib {
    template <typename T>
    class UniquePtr
        : public SmartPtr<T> {
    public:
        inline UniquePtr();
        inline UniquePtr(T* ptr);
        inline UniquePtr(T src);
        inline UniquePtr(const UniquePtr& src);
        ~UniquePtr();

        template <typename TPtr>
        friend bool operator==(const UniquePtr<TPtr> &a, const UniquePtr<TPtr> &b);
        template <typename TPtr>
        friend bool operator!=(const UniquePtr<TPtr> &a, const UniquePtr<TPtr> &b);

        inline UniquePtr<T>& operator=(const UniquePtr<T>& src) {
            m_isOwner = false;
            this->m_ptr = src.m_ptr;
            return *this;
        }

        inline bool operator!() {
            return !this->m_ptr;
        }

        inline bool IsOwner() const { return m_isOwner; }

    private:
        bool m_isOwner;

    private:
        struct _BOOL { bool value = false; };
        typedef std::unordered_map<uintptr_t, _BOOL> _HANDELED_HASH;

        inline static _HANDELED_HASH HandeledPtrs() {
            static _HANDELED_HASH s_handeledPtrs;
            return s_handeledPtrs;
        }

    };

    template <typename T>
    inline UniquePtr<T>::UniquePtr()
        : m_isOwner(false) {
        this->m_ptr = nullptr;
    }

    template <typename T>
    inline UniquePtr<T>::UniquePtr(T* ptr)
        : m_isOwner(true) {
        assert(ptr);
        uintptr_t _address = reinterpret_cast<uintptr_t>(ptr);
        assert(!HandeledPtrs()[_address].value);
        this->m_ptr = ptr;
        HandeledPtrs()[_address].value = true;

    }
    template <typename T>
    inline UniquePtr<T>::UniquePtr(T src)
        : m_isOwner(true) {
        T *_ptr = new T(src);
        uintptr_t _address = reinterpret_cast<uintptr_t>(_ptr);
        assert(!HandeledPtrs()[_address].value);
        this->m_ptr = _ptr;
        HandeledPtrs()[_address].value = true;
    }
    template <typename T>
    inline UniquePtr<T>::UniquePtr(const UniquePtr& src)
        : m_isOwner(false) { this->m_ptr = src.m_ptr; }
    template <typename T>
    UniquePtr<T>::~UniquePtr() {
        if (m_isOwner) {
            delete this->m_ptr;
            this->m_ptr = nullptr;
        }
    }

    template <typename TPtr>
    inline bool operator== (const UniquePtr<TPtr> &a, const UniquePtr<TPtr> &b) {
        return  (!a.IsGarbage() && !b.IsGarbage()) &&
                a.Get() == b.Get();
    }
    template <typename TPtr>
    inline bool operator!= (const UniquePtr<TPtr> &a, const UniquePtr<TPtr> &b) {
        return !(a == b);
    }

}
