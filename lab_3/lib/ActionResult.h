#ifndef LAB_3_ACTIONRESULT_H
#define LAB_3_ACTIONRESULT_H

namespace lib {
    template<class Data>
    class ActionResult {
    private:
        Data data;
        bool status;

    public:
        ActionResult(Data data, bool status)
                : data(data), status(status) {};

        ActionResult(bool status)
                : status(status) {};

        Data operator*() { return data; };

        explicit operator bool() { return status; };
    };

}
#endif //LAB_3_ACTIONRESULT_H
