#ifndef LAB_2_ARRAY_H
#define LAB_2_ARRAY_H

namespace lib {
    template<class T>
    class Array {
    public:
        Array(int len) : len(len) {
            this->arr = new T[len];
        }
        T & operator [](int index) {
            if (index < this->len)
                return this->arr[index];
            else
                throw std::out_of_range("Index out range");
        };

    private:
        T * arr;
        int len;
    };
}

#endif //LAB_2_ARRAY_H
