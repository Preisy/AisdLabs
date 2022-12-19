#ifndef LAB_2_IQUEUE_H
#define LAB_2_IQUEUE_H

namespace lib {
    template<class T>
    class IQueue {
    public:
        virtual bool push(const T &data) noexcept = 0;

        virtual T pop() = 0;

        virtual bool empty() const = 0;

        virtual ~IQueue() = default;
    };
}

#endif //LAB_2_IQUEUE_H
