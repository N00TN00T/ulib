#pragma once

/*
 This file needs:
 - <assert.h>
*/

namespace ulib {

    template <typename T>
    class Queue {
    public:
        struct Node {
            T* value;
            Node* next;
        };

        inline Queue()
            : m_first(nullptr), m_last(nullptr) {}

        ~Queue() {
            while (m_first != NULL) {
                Node *_temp = m_first;
                m_first = m_first->next;
                delete _temp;
            }
        }

        /* Push value to the back of the queue */
        inline void Push(const T& value) {
            Node *_node = new Node { new T(value), nullptr };
            Node *_temp = m_last;

            if (!m_last) { m_last = _node; m_first = _node; }
            else { m_last = _node; _temp->next = _node; }
        }

        /* Insert value at the front of the queue */
        inline void Insert(const T& value)  {
            Node *_node = new Node { new T(value), nullptr };
            Node *_temp = m_first;

            m_first = _node;
            m_first->next = _temp;
        }

        /* Remove the value at the front of the queue and return it */
        inline T& Pop() {
            assert(m_first != nullptr);
            T& _ret = *m_first->value;
            Node *_garbage = m_first;
            m_first = m_first->next;
            delete _garbage;
            return _ret;

            if (!m_first) m_last = nullptr;
        }

        /* Get the value at the front of the queue */
        inline T& GetTop() { assert(m_first != NULL); return *m_first->value; }

        /* Is this queue empty; are there no elements? */
        inline bool IsEmpty() const { return !m_first; }

    private:
        Node *m_first;
        Node *m_last;
    };
}
