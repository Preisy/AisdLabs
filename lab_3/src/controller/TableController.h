#ifndef LAB_3_TABLECONTROLLER_H
#define LAB_3_TABLECONTROLLER_H

#include <sstream>
#include "Table.h"

class TableController {
    Table<int> table;

    int keysCount = 2;

public:
    enum ResponseType {
        Ok,
        inputError,
        commandError,
        smthWrong
    };

    template<class Data>
    class ActionResult {
    private:
        Data* data = nullptr;
        ResponseType status;

    public:
        ActionResult(Data && data, ResponseType status)
                : data(new Data(std::move(data))), status(status) {};

        explicit ActionResult(Data && data)
                : data(new Data(std::move(data))), status(ResponseType::Ok) {};

        explicit ActionResult(ResponseType status)
                : status(status) {};

        Data & operator*() { return *data; };

        ResponseType getStatus() { return status; }

        explicit operator bool() const { return status == ResponseType::Ok; };
    };


public:
    ResponseType printKeySpace2Array(const std::string & args) {
        if (args != "")
            return ResponseType::inputError;
        table.printKeySpace2Array();
        return ResponseType::Ok;
    }

    ResponseType add(const std::string & args) {
        std::stringstream sin(args);
        lib::Array<std::string> arr(keysCount + 1);

        for (int i = 0; i < keysCount; ++i) {
            if (!(sin >> arr[i]))
                return ResponseType::inputError;
            if (arr[i] == "-")
                return ResponseType::commandError;
        }
        if (arr[keysCount - 1][arr[keysCount - 1].size() - 1] == ':')
            arr[keysCount - 1] = arr[keysCount - 1].substr(0, arr[keysCount - 1].size() - 1);
        else
            return ResponseType::inputError;

        if (!(sin >> arr[keysCount]))
            return ResponseType::inputError;
        if ((char) sin.get() != EOF)
            return ResponseType::inputError;

        int data;
        try {
            data = std::stoi(arr[keysCount]);
        } catch (std::exception &) {
            return ResponseType::commandError;
        }
        table.push(new CompositeKey(new Key2(arr[0]), new Key1(arr[1])), data);
        return ResponseType::Ok;
    }

    ActionResult<typename lib::Array<Item<int>>::CopyRAIterator>
    find(const std::string & args) {
        std::stringstream sin(args);
        lib::Array<std::string> arr(keysCount + 1);

        for (int i = 0; i < keysCount; ++i) {
            if (!(sin >> arr[i]))
                return ActionResult<typename lib::Array<Item<int>>::CopyRAIterator>(ResponseType::inputError);
        }
        if (arr[keysCount - 1][arr[keysCount - 1].size() - 1] == ':') {
            return ActionResult<typename lib::Array<Item<int>>::CopyRAIterator>(ResponseType::inputError);
        }

        if (!(sin >> arr[keysCount])) {
            return ActionResult<typename lib::Array<Item<int>>::CopyRAIterator>(
                    table.find(CompositeKey(
                            arr[0] == "-" ? nullptr : new Key2(arr[0]),
                            arr[1] == "-" ? nullptr : new Key1(arr[1])
                    ))
            );
        }

        if ((char) sin.get() != EOF) {
            return ActionResult<typename lib::Array<Item<int>>::CopyRAIterator>(ResponseType::inputError);
        }

        int version;
        try {
            version = std::stoi(arr[keysCount]);
        } catch (std::exception &) {
            return ActionResult<typename lib::Array<Item<int>>::CopyRAIterator>(ResponseType::commandError);
        }

        return ActionResult<typename lib::Array<Item<int>>::CopyRAIterator>(
                table.find(CompositeKey(
                        arr[0] == "-" ? nullptr : new Key2(arr[0]),
                        arr[1] == "-" ? nullptr : new Key1(arr[1])
                ), version)
        );
    }


    ResponseType del(const std::string & args) {
        std::stringstream sin(args);
        lib::Array<std::string> arr(keysCount + 1);

        for (int i = 0; i < keysCount; ++i) {
            if (!(sin >> arr[i]))
                return ResponseType::inputError;
        }

        if (arr[keysCount - 1][arr[keysCount - 1].size() - 1] == ':')
            return ResponseType::inputError;

        if (!(sin >> arr[keysCount])) {
            table.del(CompositeKey(
                    arr[0] == "-" ? nullptr : new Key2(arr[0]),
                    arr[1] == "-" ? nullptr : new Key1(arr[1])
            ));
            return ResponseType::Ok;
        }
        if ((char) sin.get() != EOF)
            return ResponseType::inputError;

        int version;
        try {
            version = std::stoi(arr[keysCount]);
        } catch (std::exception &) {
            return ResponseType::commandError;
        }

        table.del(CompositeKey(
                arr[0] == "-" ? nullptr : new Key2(arr[0]),
                arr[1] == "-" ? nullptr : new Key1(arr[1])
        ), version);

        return ResponseType::Ok;
    }


    ResponseType print(const std::string & args) {
        if (args != "")
            return ResponseType::inputError;
        table.print();
        return ResponseType::Ok;
    }

};

#endif //LAB_3_TABLECONTROLLER_H
