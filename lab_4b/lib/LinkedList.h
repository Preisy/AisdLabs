#ifndef LAB_3_LINKEDLIST_H
#define LAB_3_LINKEDLIST_H

#include <utility>

namespace lib {

    template<class T>
    class LinkedList;

    template<class T>
    bool operator==(const LinkedList<T> & el1, const LinkedList<T> & el2) {
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
    class LinkedList : public IList<T> {
    private:
        friend bool operator==<T>(const LinkedList & el1, const LinkedList & el2);

        class LinkedListException : public std::exception {
        private:
            std::string m_error;

        public:
            explicit LinkedListException(std::string error) : m_error(std::move(error)) {}

            const char* what() const noexcept override { return m_error.c_str(); }
        };

        class Node {
        public:
            Node* next = nullptr;
            T* data;

        public:
            explicit Node(const T & data) : data(new T(data)) {};

            explicit Node(T && data) : data(new T(std::move(data))) {};

            Node(const T & data, Node* next) : data(new T(data)), next(next) {};

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

    public:
        class FIterator {
            Node* elem = nullptr;
        public:
            explicit FIterator(Node* _head) : elem(_head) {}

            FIterator & operator++() {
                elem = elem->next;
                return *this;
            }

            FIterator operator++(int) {
                FIterator retval = *this;
                ++(*this);
                return retval;
            }

            bool operator==(FIterator other) const { return elem == other.elem; }

            bool operator!=(FIterator other) const { return elem != other.elem; }

            T & operator*() { return *elem->data; }
        };

        FIterator begin() const { return FIterator(head); }

        FIterator end() const { return FIterator(nullptr); }

    public:
        LinkedList(const LinkedList & ll) = default;

        LinkedList & operator=(const LinkedList & ll) noexcept = default;

        LinkedList(LinkedList && ll) noexcept
                : head(ll.head),
                  tail(ll.tail),
                  len(ll.len) {
            ll.head = nullptr;
            ll.tail = nullptr;
        }

        LinkedList & operator=(LinkedList && ll) noexcept {
            if (&ll == this)
                return *this;

            delete head;
            delete tail;

            head = ll.head;
            tail = ll.tail;
            len = ll.len;


            ll.head = nullptr;
            ll.tail = nullptr;

            return *this;
        }


    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        int len = 0;
    public:
        LinkedList() = default;

        ~LinkedList() {
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
            Node* tmp = new Node(data);
            if (this->tail == nullptr) {
                this->head = this->tail = tmp;
            } else {
                this->tail->next = tmp;
                this->tail = tmp;
            }
            ++len;
        }

        void push(T && data) {
            Node* tmp = new Node(std::move(data));
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
                        delete tmp;
                        --(this->len);
                        return true;
                    } else {
                        Node* tmp = it->next;
                        it->setNext(it->next->next);
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
                throw LinkedListException("Index out of range");

            if (index == 0) {
                Node* tmp = this->head;
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
                        delete tmp;
                        --(this->len);
                        return data;
                    } else {
                        Node* tmp = it->next;
                        const T & data = *tmp->data;
                        it->setNext(it->next->next);
                        delete tmp;
                        --(this->len);
                        return data;
                    }
                }
                it = it->next;
            }
            throw LinkedListException("wtf???");
        }

    public:
        T & operator[](int index) override {
            if (index < 0 || index >= this->len)
                throw LinkedListException("Index out of range");


            if (index == 0) {
                return *this->head->data;
            }

            if (index == this->len - 1) {
                return *this->tail->data;
            }

            Node* it = this->head;
            for (int i = 1; it->next != nullptr; ++i) {
                if (i == index) {
                    return *it->next->data;
                }
                it = it->next;
            }
        }

        const T & operator[](int index) const override {
            if (index < 0 || index >= this->len)
                throw LinkedListException("Index out of range");


            if (index == 0) {
                return *this->head->data;
            }

            if (index == this->len - 1) {
                return *this->tail->data;
            }

            Node* it = this->head;
            for (int i = 1; it->next != nullptr; ++i) {
                if (i == index) {
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

#endif //LAB_3_LINKEDLIST_H
