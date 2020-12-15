#pragma once
#ifndef _QUEUE_H
#define _QUEUE_H

template <typename T>
struct Queue {
private:
    struct El {
        T Value;
        El* Next;
        El* Previous;
    };

    El* m_first;
    El* m_last;
public:
    Queue() {
        m_first = m_last = nullptr;
    }

    Queue(const Queue& f) {
        El* it = f.m_first;
        while (it) {
            Insert(it->Value);
            it = it->Next;
        }
    }

    ~Queue() {
        while (m_first) {
            El* tmp = m_first;
            m_first = m_first->Next;
            delete tmp;
        }
    }

    void Insert(T Value) {
        m_last = new El{ Value, nullptr, m_last };
        if (!m_first)
            m_first = m_last;
        else
            m_last->Previous->Next = m_last;
    }

    T Remove() {
        T Value = m_last->Value;
        El* tmp = m_last;

        if (m_last->Previous) {
            m_last = m_last->Previous;
            m_last->Next = nullptr;
        }
        else {
            m_last = nullptr;
            m_first = nullptr;
        }

        delete tmp;
        return Value;
    }

    bool Contains(T Value) const {
        El* el = m_first;
        while (el) {
            if (el->Value == Value)
                return true;

            el = el->Next;
        }

        return false;
    }

    template <class E>
    using ApplyFunction = void (E::*) (T);

    template <class E>
    void Processing(ANetworkElement *element, ApplyFunction<E> f) {
        El* el = m_first;
        while (el) {
            (element->*f)(el->Value);

            el = el->Next;
        }
    }

    template <class E>
    using ApplyFunctionProcess = void(E::*) ();

    template <class E>
    void Processing(ApplyFunctionProcess<E> f) {
        El* el = m_first;
        while (el) {
            ((el->Value)->*f)();

            el = el->Next;
        }
    }

    bool IsEmpty() const {
        return m_first == nullptr;
    }
};

#endif // !_QUEUE_H