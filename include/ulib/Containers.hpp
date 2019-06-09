#pragma once

/*
 This file needs:
 - <string.h>
 - <assert.h>
*/

namespace ulib {
    template <typename TContainer, typename TValue>
    class Iterator {
    public:
        inline Iterator(TContainer& container, const uint64_t& value)
            : m_container(container), m_value(value) {}

        inline Iterator& operator++() {
            m_value += 1;
            return *this;
        }

        template <typename Tc, typename Tv>
        friend bool operator!=(const Iterator<Tc, Tv> &a, const Iterator<Tc, Tv> &b);

        inline TValue& operator*() {
            assert(m_value < m_container.GetLength());
            
            return m_container.Get(m_value);
        }

        inline const uint64_t& GetValue() const { return m_value; }

    private:
        TContainer& m_container;
        uint64_t m_value;
    };

    template <typename Tc, typename Tv>
    bool operator!=(const Iterator<Tc, Tv> &a, const Iterator<Tc, Tv> &b) {
        return a.GetValue() != b.GetValue();
    }
}

#include "Containers/Array.hpp"
#include "Containers/Queue.hpp"
#include "Containers/Stack.hpp"
#include "Containers/GrowingArray.hpp"
