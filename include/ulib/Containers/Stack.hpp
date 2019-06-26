#pragma once

/*
 This file needs:
 - <assert.h>
*/

namespace ulib {

    template <typename T>
    class Stack {
    public:
        struct Node {
            T value;
            Node* next;
        };

        inline Stack()
            : m_top(nullptr) {}

        ~Stack() {
            while (m_top != NULL) {
                Node *_temp = m_top;
                m_top = m_top->next;
                delete _temp;
            }
        }

        /* Push a value to the top of the stack */
        inline void Push(const T& value) {
            Node *_node = new Node { value, nullptr };
            Node *_temp = m_top;

            m_top = _node;
            m_top->next = _temp;
        }

        /* Remove the value at the top of the stack; the last pushed value, and return it */
        inline T Pop() {
            assert(m_top != nullptr);
            T _ret = m_top->value;
            Node *_garbage = m_top;
            m_top = m_top->next;
            delete _garbage;
            return _ret;
        }

        /* Get the value at the top of the stack */
        inline T& GetTop() { assert(m_top != NULL); return m_top->value; }

        /* Is this stack empty; are there no elements? */
        inline bool IsEmpty() const { return !m_top; }

    private:
        Node *m_top;
    };
}
