#ifndef  LAB_2_QueueList_H
#define  LAB_2_QueueList_H

#include <iostream>

namespace lib {


    template<class T>
    class Queue {
    private:
        class QueueException : public std::exception {
        private:
            std::string m_error;

        public:
            explicit QueueException(std::string error) : m_error(std::move(error)) {}

            const char* what() const noexcept override { return m_error.c_str(); }
        };

        class Node {
        private:
            explicit Node(const T & data) : _data(data) {};

            Node(const T & data, Node* next) : _data(data), _next(next) {};

        public:
            const T & getData() const { return this->_data; }

            Node* getNext() const { return this->_next; }

            void setNext(Node* next) noexcept { this->_next = next; }

            friend Queue;

        private:
            Node* _next = nullptr;
            T _data;
        };

        Node* head = nullptr;
        Node* tail = nullptr;

    public:
        Queue() = default;

        ~Queue() {
            Node* it = head;
            while (it != nullptr) {
                Node* tmp = it;
                it = it->getNext();
                delete tmp;
            }
        }

        bool push(const T & data) noexcept {
            Node* tmp = new Node(data);

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
            Node* tmp = this->head;
            T data = tmp->getData();
            if (head == tail) {
                head = tail = nullptr;
            } else {
                this->head = this->head->getNext();
            }
            delete tmp;
            return data;
        }

        bool empty() const { return this->head == nullptr; }
    };

}

#endif