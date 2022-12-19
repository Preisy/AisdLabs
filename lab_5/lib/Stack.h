#ifndef LAB_5_STACK_H
#define LAB_5_STACK_H

#include "iostream"
#include "Deq.h"
#include "Array.h"

namespace lib {
    template<class T>
    class Stack {
    private:
        static const int capacity = 10;
        lib::Deq<lib::Array<T, capacity>> ll;
        int n = 0;

    public:
        void push(const T & el) {
            if (n % capacity == 0) {
                ll.push(lib::Array<T, capacity>());
            }
            auto it = ll.end() - 1;
            int h = (n++) % capacity;

            (*it)[h] = el;
        }

        T pop() {
            auto it = ll.end() - 1;
            --n;
            if (n % capacity == 0) {
                ll.removeAt(ll.getLength() - 1);
            }
        }
    };
}


#endif //LAB_5_STACK_H
