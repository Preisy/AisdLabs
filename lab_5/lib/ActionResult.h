#ifndef LAB_3_ACTIONRESULT_H
#define LAB_3_ACTIONRESULT_H

namespace lib {
    template<class Data>
    class ActionResult {
    private:
        Data data;
        bool status;

    public:
        ActionResult(Data && data, bool status)
                : data(std::move(data)), status(status) {};

        explicit ActionResult(Data && data)
                : data(std::move(data)), status(true) {};

        explicit ActionResult(bool status)
                : status(status), data(Data()) {};

        Data & operator*() { return data; };

        explicit operator bool() const { return status; };
    };

}
#endif //LAB_3_ACTIONRESULT_H
