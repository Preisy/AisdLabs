#ifndef LAB_2_ARRAY_H
#define LAB_2_ARRAY_H

#include "string.h"

namespace lib {

    template<class T, int defaultLength>
    class Array;

    template<class T, int defaultLength>
    bool operator==(const Array<T, defaultLength> & el1, const Array<T, defaultLength> & el2) {
        if (el1.getLength() != el2.getLength())
            return false;
        for (int i = 0; i < el1.getLength(); ++i) {
            if (el1[i] != el2[i])
                return false;
        }
        return true;
    }

    template<class T, int defaultLength = 0>
    class Array {
    public:
        Array() : len(defaultLength) {
            if (defaultLength == 0) {
                this->arr = nullptr;
            } else {
                this->arr = new T[defaultLength];
            }
        };

        explicit Array(int len) : len(len) {
            this->arr = new T[len];
        }

        ~Array() {
            delete[] this->arr;
        }

        T & operator[](int index) {
            if (index < this->len)
                return this->arr[index];
            else
                throw std::out_of_range("Index out range");
        };

        const T & operator[](int index) const {
            if (index < this->len)
                return this->arr[index];
            else
                throw std::out_of_range("Index out range");
        };

        int getLength() const { return this->len; };

    private:
        T* arr;
        int len;

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
        typedef _RandomAccessIterator<Array<T>> CopyRAIterator;

        RAIterator begin() const { return RAIterator(arr, 0, len); }

        RAIterator end() const { return RAIterator(arr, len, len); }

        CopyRAIterator copyBegin() const { return CopyRAIterator(*this, 0, len, false); }

//        CopyRAIterator copyEnd() const { return CopyRAIterator(arr + len, len, len); }

        CopyRAIterator moveBegin() const { return CopyRAIterator(std::move(*const_cast<Array<T>*>(this)), 0, len); }

//        CopyRAIterator moveEnd() const { return CopyRAIterator(arr + len, len, len); }



    public:
        Array(const Array & _arr) : len(_arr.len) {
            arr = new T[len];
            for (int i = 0; i < len; ++i) {
                arr[i] = _arr.arr[i];
            }
        }

        Array & operator=(const Array & _arr) noexcept {
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

        Array(Array && _arr) noexcept
                : arr(_arr.arr), len(_arr.len) {
            _arr.arr = nullptr;
        }

        Array & operator=(Array && _arr) noexcept {
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

#endif //LAB_2_ARRAY_H
