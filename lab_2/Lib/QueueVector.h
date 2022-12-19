#ifndef LAB_2_QUEUEVECTOR_H
#define LAB_2_QUEUEVECTOR_H

#include "IQueue.h"
#include "Array.h"

namespace lib {

    template<class T>
    class QueueArray : public IQueue<T> {
    public:
        QueueArray(int len) : arr(Array<T>(len)), tail(-1), head(-1), length(0) {}

        virtual bool push(const T &data) noexcept {
            ++this->length;
            if (this->tail == -1 && this->head == -1) {
                this->tail = this->head = this->len - 1;
                this->arr[this->tail] = data;
                return true;
            } else if (this->tail == 0) this->tail = this->len - 1;
            else --this->tail;

            if (this->tail == this->head) {
                if (this->head == 0) this->head = this->len - 1;
                else --this->head;
            }
            this->arr[this->tail] = data;
            return true;
        }

        virtual T pop() {
            if (this->empty()) throw QueueException("Queue is empty");

            if (this->head == -1 && this->tail == -1) exit(-1);
            int data = this->arr[this->head];

            if (this->head == this->tail) this->head = this->tail = -1;
            else if (this->head == 0) this->head = this->len - 1;
            else --this->head;

            --this->length;

            return data;
        }

        virtual bool empty() const {
            return this->length == 0;
        }

    private:
        Array<T> arr;
        int head;
        int tail;
        int length;
    };

}

#endif //LAB_2_QUEUEVECTOR_H
