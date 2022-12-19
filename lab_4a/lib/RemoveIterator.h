#ifndef LAB_3_REMOVEITERATOR_H
#define LAB_3_REMOVEITERATOR_H

namespace lib {

    template<class T>
    class RemoveIterator {
    public:
        virtual bool remove() = 0;

        virtual ~RemoveIterator() = default;
    };

}

#endif //LAB_3_REMOVEITERATOR_H
