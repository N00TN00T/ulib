#pragma once

/*
 This file needs:
 - 
*/

/* An interface for all smart pointer types */

namespace ulib {
    template <typename T>
    class SmartPtr {
    public:

        inline T* Get() const { return m_ptr; }

        inline T* operator->() const { return this->Get(); }

        inline T& operator*() { return *this->Get(); }

        inline void Delete() { delete m_ptr; m_ptr = NULL; m_isGarbage = true; }

        inline const bool& IsGarbage() const { return m_isGarbage; }

    protected:
        T* m_ptr;
    private:
        bool m_isGarbage;
    };
}
