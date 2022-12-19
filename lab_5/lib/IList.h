#ifndef LAB_2_IQUEUE_H
#define LAB_2_IQUEUE_H

namespace lib {
    template<class T>
    class IList {
    public:
//        virtual void push(const T & data) = 0;

        virtual bool remove(const T & el) = 0;

        virtual const T & removeAt(int index) = 0;

        virtual T & operator[](int index) = 0;

        virtual const T & operator[](int index) const = 0;


        virtual bool contains(const T & el) const = 0;

        virtual bool empty() const = 0;

        virtual int getLength() const = 0;

        virtual ~IList() = default;
    };
}

#endif //LAB_2_IQUEUE_H
