#ifndef  LAB_2_QueueList_H
#define  LAB_2_QueueList_H
#include <iostream>

namespace lib {

    class QueueException : public std::exception {
    private:
        std::string m_error;

    public:
        explicit QueueException(std::string error) : m_error(std::move(error)) {}

        const char *what() const noexcept override { return m_error.c_str(); }
    };


    template<class T>
    class QueueList;

    template<class T>
    class Node {
    private:
        explicit Node(const T &data) : _data(data) {};

        Node(const T &data, Node<T> *next) : _data(data), _next(next) {};

    public:
        const T &getData() const { return this->_data; }

        Node<T> *getNext() const { return this->_next; }

        void setNext(Node<T> *next) noexcept { this->_next = next; }

        friend QueueList<T>;

    private:
        Node<T> *_next = nullptr;
        T _data;
    };

    template<class T>
    class QueueList : public IQueue<T> {
    public:
        QueueList() = default;

        ~QueueList() {
            Node<T> *it = head;
            while (it != nullptr) {
                Node<T> *tmp = it;
                it = it->getNext();
                delete tmp;
            }
        }

        bool push(const T &data) noexcept {
            Node<T> *tmp = new Node<T>(data);

            if (this->head == nullptr) {
                this->head = tmp;
                this->tail = tmp;
            } else {
                this->tail->setNext(tmp);
                this->tail = tmp;
            }
            return true;
        }

        T pop() {
            if (this->empty()) throw QueueException("Queue is empty");
            Node<T> *tmp = this->head;
            T data = tmp->getData();
            this->head = this->head->getNext();
            delete tmp;
            return data;
        }

        bool empty() const { return this->head == nullptr; }

    private:

        Node<T> *head = nullptr;
        Node<T> *tail = nullptr;
    };

}

#endif