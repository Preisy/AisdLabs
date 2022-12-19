#ifndef LAB_4_MAPCONTROLLER_H
#define LAB_4_MAPCONTROLLER_H

#include "lib.h"
#include "AVLMap.h"
#include "time.h"

class MapController {
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
        Data* data = nullptr; // todo вообще оно должно течь
        ResponseType status;

    public:
        ActionResult(Data && data, ResponseType status)
                : data(new Data(std::move(data))), status(status) {};

        explicit ActionResult(Data && data)
                : data(new Data(std::move(data))), status(ResponseType::Ok) {};

        explicit ActionResult(const ResponseType & status)
                : status(status) {};

        Data & operator*() { return *data; };

        ResponseType getStatus() { return status; }

        explicit operator bool() const { return status == ResponseType::Ok; };
    };

private:
    lib::AVLMap<int, std::string> mp;


public:
    ResponseType add(const std::string & args) {
        std::pair<int, std::string> p;
        std::string tmp;
        int i = 0;
        for (; i < args.size(); ++i) {
            if (args[i] == ' ') break;
            tmp += args[i];
        }
        try {
            p.first = std::stoi(tmp);
        } catch (std::exception &) {
            return ResponseType::commandError;
        }


        if (i == args.size() - 1)
            return ResponseType::commandError;

        for (; i < args.size(); ++i) {
            p.second += args[i];
        }

        mp.add(p);
        return ResponseType::Ok;
    }

    ResponseType mock(const std::string & args) {
        if (args != "") return ResponseType::commandError;

        srand(time(0));

        int n = 30;
        int arr[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = 1 + rand() % 99;
            std::cout << arr[i];
            if (i != n - 1)
                std::cout << ", ";
            mp.add({arr[i], ""});
        }
        std::cout << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << "add " << arr[i] << "; ";
        }
        std::cout << std::endl;
    }

    ResponseType specialTreeTraversal(const std::string & args) {
        if (args == "")
            mp.specialTreeTraversal();

        int index = strchr(args.c_str(), ' ') - args.c_str();
        if (0 <= index && index < args.size())
            return ResponseType::commandError;

        int n;
        try {
            n = std::stoi(args);
        } catch (std::exception &) {
            return ResponseType::commandError;
        }

        mp.specialTreeTraversal(n);

        return ResponseType::Ok;
    }

    ActionResult<std::string> find(const std::string & args) {
        int index = strchr(args.c_str(), ' ') - args.c_str();
        if (0 <= index && index < args.size())
            return ActionResult<std::string>(ResponseType::commandError);

        int n;
        try {
            n = std::stoi(args);
        } catch (std::exception &) {
            return ActionResult<std::string>(ResponseType::commandError);
        }

        lib::ActionResult<std::string> j = mp.find(n);
        if (j) {
            return ActionResult<std::string>(std::move(*j));
        } else {
            return ActionResult<std::string>(std::string());
        }
    }

    ActionResult<std::string> specialFind(const std::string & args) {
        int index = strchr(args.c_str(), ' ') - args.c_str();
        if (0 <= index && index < args.size())
            return ActionResult<std::string>(ResponseType::commandError);

        int n;
        try {
            n = std::stoi(args);
        } catch (std::exception &) {
            return ActionResult<std::string>(ResponseType::commandError);
        }

        int* answer = mp.specialFind(n);

        if (answer == nullptr) {
            return ActionResult<std::string>(ResponseType::smthWrong);
        } else {
            return ActionResult<std::string>(std::move(std::to_string(*answer)));

        }
    }

    ResponseType del(const std::string & args) {
        int index = strchr(args.c_str(), ' ') - args.c_str();
        if (0 <= index && index < args.size())
            return ResponseType::commandError;

        int k;
        try {
            k = std::stoi(args);
        } catch (std::exception &) {
            return ResponseType::commandError;
        }
        mp.remove(k);

        return ResponseType::Ok;
    }

    ResponseType print(const std::string & args) {
        if (args != "") return ResponseType::commandError;

        mp.print();

        return ResponseType::Ok;
    }

    ResponseType write(const std::string & args) {
        if (args != "") return ResponseType::commandError;

        mp.write();

        return ResponseType::Ok;
    }

};


#endif //LAB_4_MAPCONTROLLER_H
