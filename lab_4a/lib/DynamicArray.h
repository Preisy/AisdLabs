#ifndef LAB_4_DYNAMICARRAY_H
#define LAB_4_DYNAMICARRAY_H

#include "IList.h"


namespace lib {
    template<class T>
//    class DynamicArray : IList<T> {
    class DynamicArray {
    private:
        T* arr = nullptr;
        int bufLength = 10;
        int len = 0;

    public:
        DynamicArray() {
            this->arr = new T[bufLength];
        };


        ~DynamicArray() {
            delete[] this->arr;
        }

        T & operator[](int index) {
            if (0 <= index && index < len)
                return this->arr[index];
            else
                throw std::out_of_range("Index out range");
        };

        const T & operator[](int index) const {
            if (0 <= index && index < len)
                return this->arr[index];
            else
                throw std::out_of_range("Index out range");
        };

        int getLength() const { return this->len; };

        void push(const T & data) {
            if (len == bufLength) {
                bufLength *= 2;
                T* tmp = new T[bufLength];
                for (int i = 0; i < len; ++i) {
                    tmp[i] = std::move(arr[i]);
                }
                delete[] arr;
                arr = tmp;
            }
            arr[len++] = data;
        }
        void push(T && data) {
            if (len == bufLength) {
                bufLength *= 2;
                T* tmp = new T[bufLength];
                for (int i = 0; i < len; ++i) {
                    tmp[i] = std::move(arr[i]);
                }
                delete[] arr;
                arr = tmp;
            }
            arr[len++] = data;
        }


//    private:
//        bool remove(const T & el) override {
//            for (int i = 0; i < len; ++i) {
//
//            }
//        }
//
//        const T & removeAt(int index) override {
//            return <#initializer#>;
//        }
//
//        bool contains(const T & el) const override {
//            return false;
//        }
//
//        bool empty() const override {
//            return false;
//        }


    public:
        template<class TI>
        class _RandomAccessIterator {
            TI source;
            int curIndex;
            int arrayLength;
        public:
            explicit _RandomAccessIterator(T* src, int index, int arrayLength)
                    : source(src),
                      curIndex(index),
                      arrayLength(arrayLength) {}

            explicit _RandomAccessIterator(const TI & src, int index, int arrayLength, bool moveFlag)
                    : source(TI(src)),
                      curIndex(index),
                      arrayLength(arrayLength) {}

            explicit _RandomAccessIterator(TI && src, int index, int arrayLength)
                    : source(std::move(src)), curIndex(index), arrayLength(arrayLength) {}

            bool isAtStart() {
                return curIndex == 0;
            }

            bool isEnded() {
                return curIndex >= arrayLength;
            }

            _RandomAccessIterator & operator++() {
                ++curIndex;
                return *this;
            }

            _RandomAccessIterator operator++(int) {
                _RandomAccessIterator retval = *this;
                ++(*this);
                return retval;
            }

            _RandomAccessIterator & operator--() {
                --curIndex;
                return *this;
            }

            _RandomAccessIterator operator--(int) {
                _RandomAccessIterator retval = *this;
                --(*this);
                return retval;
            }

            bool operator==(_RandomAccessIterator other) const {
                return (source == other.source
                        && curIndex == other.curIndex);
            }

            bool operator!=(_RandomAccessIterator other) const {
                return (source != other.source
                        || curIndex != other.curIndex);
            }

            T & operator*() { return source[curIndex]; }

        public:
            _RandomAccessIterator(const _RandomAccessIterator & it)
                    : source(TI(it.source)),
                      curIndex(it.curIndex),
                      arrayLength(it.arrayLength) {}

            _RandomAccessIterator & operator=(_RandomAccessIterator && it) noexcept {
                if (&it == this)
                    return *this;

//                delete source; // он и не нужен

                source = std::move(it.source);
                curIndex = it.curIndex;
                arrayLength = it.arrayLength;

                it.source = TI();
                it.curIndex = 0;
                it.arrayLength = 0;

                return *this;
            }
        };

        typedef _RandomAccessIterator<T*> RAIterator;
        typedef _RandomAccessIterator<DynamicArray<T>> CopyRAIterator;

        RAIterator begin() const { return RAIterator(arr, 0, len); }

        RAIterator end() const { return RAIterator(arr, len, len); }

        CopyRAIterator copyBegin() const { return CopyRAIterator(*this, 0, len, false); }

//        CopyRAIterator copyEnd() const { return CopyRAIterator(arr + len, len, len); }

        CopyRAIterator moveBegin() const { return CopyRAIterator(std::move(*const_cast<DynamicArray<T>*>(this)), 0, len); }

//        CopyRAIterator moveEnd() const { return CopyRAIterator(arr + len, len, len); }



    public:
        DynamicArray(const DynamicArray & _arr) : len(_arr.len) {
            arr = new T[len];
            for (int i = 0; i < len; ++i) {
                arr[i] = _arr.arr[i];
            }
        }

        DynamicArray & operator=(const DynamicArray & _arr) noexcept {
            if (&_arr == this)
                return *this;

            delete[] arr;

            len = _arr.len;
            arr = new T[len];
            for (int i = 0; i < len; ++i) {
                arr[i] = _arr.arr[i];
            }

            return *this;
        }

        DynamicArray(DynamicArray && _arr) noexcept
                : arr(_arr.arr), len(_arr.len) {
            _arr.arr = nullptr;
        }

        DynamicArray & operator=(DynamicArray && _arr) noexcept {
            if (&_arr == this)
                return *this;

            delete[] arr;

            arr = _arr.arr;
            len = _arr.len;

            _arr.arr = nullptr;

            return *this;
        }
    };


}

#endif //LAB_4_DYNAMICARRAY_H
