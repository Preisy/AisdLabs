#ifndef LAB_3_DEQ_H
#define LAB_3_DEQ_H

#include <utility>
#include "RemoveIterator.h"
#include "IList.h"

namespace lib {

    template<class T>
    class Deq;

    template<class T>
    bool operator==(const Deq<T> & el1, const Deq<T> & el2) {
        if (el1.len != el2.len)
            return false;
        auto h1 = el1.head;
        auto h2 = el1.head;
        while (h1 != nullptr) {
            if (h1 != h2)
                return false;
            h1 = h1->next;
            h2 = h2->next;
        }

        std::cout << "LL ==" << std::endl;
        return true;
    }

    template<class T>
    class Deq : public IList<T> {
    private:
        friend bool operator==<T>(const Deq & el1, const Deq & el2);

        class DeqException : public std::exception {
        private:
            std::string m_error;

        public:
            explicit DeqException(std::string error) : m_error(std::move(error)) {}

            const char* what() const noexcept override { return m_error.c_str(); }
        };

        class Node {
        public:
            Node* next = nullptr;
            Node* prev = nullptr;
            T* data;

        public:
            Node(const T & data, Node* prev) : data(new T(data)), prev(prev) {};

            Node(T && data, Node* prev) : data(new T(std::move(data))), prev(prev) {};

        public:
            Node(const Node &) = default;

            Node & operator=(const Node &) = default;

            Node(Node && node) noexcept
                    : next(node.next), data(node.data) {
                node.next = nullptr;
                node.data = nullptr;
            }

            Node & operator=(Node && node) noexcept {
                if (&node == this)
                    return *this;

                delete next;
                delete data;

                next = node.next;
                data = node.data;

                node.next = nullptr;
                node.data = nullptr;

                return *this;
            }

            ~Node() {
                delete data;
            }

        public:
            void setNext(Node* next) noexcept { this->next = next; }
        };

        friend class FIterator;
    public:
        class RAIterator : public RemoveIterator<T> {
            Node* elem = nullptr;
            Deq<T>* source;
        public:
            RAIterator(Deq<T>* src, Node* prev, Node* el) : elem(el), source(src) {
                if (src == nullptr)
                    exit(-1);
            }

            RAIterator & operator++() {
                elem = elem->next;
                return *this;
            }

            RAIterator operator++(int) {
                RAIterator retval = *this;
                ++(*this);
                return retval;
            }

            RAIterator & operator--() {
                if (elem == nullptr)
                    elem = source->tail;
                else
                    elem = elem->prev;
                return *this;
            }

            RAIterator operator--(int) {
                RAIterator retval = *this;
                ++(*this);
                return retval;
            }

            RAIterator & operator+(int num) {
                for (int i = 0; i < num; ++i) {
                    ++(*this);
                }
                return *this;
            }
            RAIterator & operator-(int num) {
                for (int i = 0; i < num; ++i) {
                    --(*this);
                }
                return *this;
            }

            bool remove() override {
                if (elem == nullptr || source->head == nullptr || source->tail == nullptr)
                    return false;
                Node* tmp = elem;
                if (source->head == source->tail) {
                    source->head = source->tail = elem = nullptr;
                } else if (source->head == elem) {
                    if (source->head->next != nullptr)
                        source->head->next->prev = nullptr;
                    source->head = elem->next;
                    elem = elem->next;
                } else if (source->tail == elem) {
                    if (source->tail->prev != nullptr)
                        source->tail->prev->next = nullptr;
                    source->tail = elem->prev;
                    elem = nullptr;
                } else {
                    elem->prev->next = elem->next;
                    elem->next->prev = elem->prev;
                    elem = elem->next;
                }
                delete tmp;
                --source->len;
                return true;
            }

            bool operator==(RAIterator other) const { return elem == other.elem; }

            bool operator!=(RAIterator other) const { return elem != other.elem; }

            T & operator*() { return *elem->data; }
        };

        RAIterator begin() const { return RAIterator(const_cast<lib::Deq<T>*>(this), nullptr, head); }
        RAIterator* pBegin() const { return new RAIterator(const_cast<lib::Deq<T>*>(this), nullptr, head); }

//        FIterator end() const { return FIterator(this, tail, nullptr); }
        RAIterator end() const { return RAIterator(const_cast<lib::Deq<T>*>(this), tail, nullptr); }
        RAIterator* pEnd() const { return new RAIterator(const_cast<lib::Deq<T>*>(this), tail, nullptr); }



    public:
        Deq(const Deq & ll) = delete;

        Deq & operator=(const Deq & ll) noexcept = delete;

        Deq(Deq && ll) noexcept
                : head(ll.head),
                  tail(ll.tail),
                  len(ll.len),
                  prev(ll.prev),
                  prevIndex(ll.prevIndex) {
            ll.head = nullptr;
            ll.tail = nullptr;
            ll.prev = nullptr;
        }

        Deq & operator=(Deq && ll) noexcept {
            if (&ll == this)
                return *this;

            if (head != tail) {
                delete head;
                if (len != 1) {
                    delete tail;
                }
                delete tail;
            } else {
                delete head;
            }

            head = ll.head;
            tail = ll.tail;
            len = ll.len;
            tail = ll.prev;
            prevIndex = ll.prevIndex;


            ll.head = nullptr;
            ll.tail = nullptr;
            ll.prev = nullptr;
            ll.len = 0;

            return *this;
        }


    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        int len = 0;
    public:
        Deq() = default;

        ~Deq() {
            Node* jt = nullptr;
            Node* it = head;
            while (it != nullptr) {
                delete jt;
                jt = it;
                it = it->next;
            }
            delete jt;
        }

        void push(const T & data) {
            Node* tmp = new Node(data, this->tail);
            if (this->tail == nullptr) {
                this->head = this->tail = tmp;
            } else {
                this->tail->next = tmp;
                this->tail = tmp;
            }
            ++len;
        }

        void push(T && data) {
            Node* tmp = new Node(std::move(data), this->tail);
            if (this->tail == nullptr) {
                this->head = this->tail = tmp;
            } else {
                this->tail->next = tmp;
                this->tail = tmp;
            }
            ++len;
        }

        bool remove(const T & el) override {
            Node* it = this->head;
            if (*it->data == el) {
                Node* tmp = this->head;
                if (tmp->next != nullptr)
                    tmp->next->prev = nullptr;
                this->head = this->head->next;
                delete tmp;
                --(this->len);
                return true;
            }
            for (; it->next != nullptr; it = it->next) {
                if (*it->next->data == el) {
                    if (it->next == this->tail) {
                        Node* tmp = this->tail;
                        this->tail = it;
                        it->next = nullptr;
                        delete tmp;
                        --(this->len);
                        return true;
                    } else {
                        Node* tmp = it->next;
                        it->setNext(it->next->next);
                        if (tmp->next != nullptr)
                            tmp->next->prev = it;
                        delete tmp;
                        --(this->len);
                        return true;
                    }
                }
            }
            return false;
        }

        const T & removeAt(int index) override {
            if (index < 0 || index >= this->len)
                throw DeqException("Index out of range");

            if (index == 0) {
                Node* tmp = this->head;
                if (tmp->next != nullptr)
                    tmp->next->prev = nullptr;
                const T & data = *tmp->data;
                this->head = this->head->next;
                delete tmp;
                --(this->len);
                return data;
            }
            Node* it = this->head;
            for (int i = 1; it->next != nullptr; ++i) {
                if (i == index) {
                    if (it->next == this->tail) {
                        Node* tmp = this->tail;
                        const T & data = *tmp->data;
                        this->tail = it;
                        it->next = nullptr;
                        delete tmp;
                        --(this->len);
                        return data;
                    } else {
                        Node* tmp = it->next;
                        const T & data = *tmp->data;
                        it->setNext(it->next->next);
                        if (tmp->next != nullptr)
                            tmp->next->prev = it;
                        delete tmp;
                        --(this->len);
                        return data;
                    }
                }
                it = it->next;
            }
            throw DeqException("wtf???");
        }

    private:
        mutable Node* prev = nullptr;
        mutable int prevIndex = -2;

    public:
        T & operator[](int index) override {
            if (index < 0 || index >= this->len)
                throw DeqException("Index out of range");

            if (prevIndex == index - 1) {
                prev = prev->next;
                prevIndex = index;
                return *prev->data;
            }

            if (index == 0) {
                prev = this->head;
                prevIndex = 0;
                return *this->head->data;
            }

            if (index == this->len - 1) {
                prev = this->tail;
                prevIndex = this->len - 1;
                return *this->tail->data;
            }

            Node* it = this->head;
            for (int i = 1; it->next != nullptr; ++i) {
                if (i == index) {
                    prev = it->next;
                    prevIndex = i;
                    return *it->next->data;
                }
                it = it->next;
            }
        }

        const T & operator[](int index) const override {
            if (index < 0 || index >= this->len)
                throw DeqException("Index out of range");

            if (prevIndex == index - 1) {
                prev = prev->next;
                prevIndex = index;
                return *prev->data;
            }

            if (index == 0) {
                prev = this->head;
                return *this->head->data;
            }

            if (index == this->len - 1) {
                prev = this->tail;
                prevIndex = this->len - 1;
                return *this->tail->data;
            }

            Node* it = this->head;
            for (int i = 1; it->next != nullptr; ++i) {
                if (i == index) {
                    prev = it->next;
                    prevIndex = i;
                    return *it->next->data;
                }
                it = it->next;
            }
        }


        bool contains(const T & el) const override {
            for (Node* it = this->head; it != nullptr; it = it->next) {
                if (*it->data == el) {
                    return true;
                }
            }
            return false;
        }

        bool empty() const override {
            return len == 0;
        }

        int getLength() const override {
            return len;
        }
    };
}
#endif //LAB_3_DEQ_H
