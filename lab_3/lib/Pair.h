#ifndef LAB_3_PAIR_H
#define LAB_3_PAIR_H

namespace lib {
    template<class A, class B>
    class Pair {
    private:
        A first;
        B second;
    public:
        const A & getFirst() const { return first; }

        void setFirst(A first) { Pair::first = first; }

        void setSecond(B second) { Pair::second = second; }

        const B & getSecond() const { return second; }

    };
}

#endif //LAB_3_PAIR_H
