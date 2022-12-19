#ifndef LAB_4_MAPCONTROLLER_H
#define LAB_4_MAPCONTROLLER_H

#include "lib.h"
#include "Digraph.h"

class GraphController {
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
        Data data; // todo вообще оно должно течь
        ResponseType status;

    public:


        ActionResult(Data && data, ResponseType status)
                : data(std::move(data)), status(status) {};

        explicit ActionResult(Data && data)
                : data(std::move(data)), status(ResponseType::Ok) {};

        explicit ActionResult(const ResponseType & status)
                : status(status), data(Data()) {};

        Data & operator*() { return data; };

        ResponseType getStatus() { return status; }

        explicit operator bool() const { return status == ResponseType::Ok; };
    };

private:
    Digraph digraph;


public:
    lib::Array<int> split(const std::string & args) {
        lib::Array<int> res(2);

        std::string tmp1;
        int i = 0;
        for (; i < args.size(); ++i) {
            if (args[i] == ' ') break;
            tmp1 += args[i];
        }
        try {
            res[0] = std::stoi(tmp1);
        } catch (std::exception &) {
            return lib::Array<int>(0);
        }


        std::string tmp2;
        for (i = i + 1; i < args.size(); ++i) {
            if (args[i] == ' ') break;
            tmp2 += args[i];
        }
        try {
            res[1] = std::stoi(tmp2);
        } catch (std::exception &) {
            return lib::Array<int>(0);
        }

        return res;
    }

//    ResponseType mock(const std::string & args) {
//        if (args != "") return ResponseType::commandError;
//
//        srand(time(0));
//
//        int n = 30;
//        int arr[n];
//        for (int i = 0; i < n; ++i) {
//            arr[i] = 1 + rand() % 99;
//            std::cout << arr[i];
//            if (i != n - 1)
//                std::cout << ", ";
//            digraph.add({arr[i], ""});
//        }
//        std::cout << std::endl;
//        for (int i = 0; i < n; ++i) {
//            std::cout << "add " << arr[i] << "; ";
//        }
//        std::cout << std::endl;
//    }

    ActionResult<lib::Array<int>> findPath(const std::string & args) {
        lib::Array<int> u = split(args);
        if (u.getLength() == 0)
            return ActionResult<lib::Array<int>>(ResponseType::commandError);

        return ActionResult<lib::Array<int>>(digraph.findPath(u[0], u[1]));
    }

    ActionResult<lib::Array<int>> findShortestPath(const std::string & args) {
        lib::Array<int> u = split(args);
        if (u.getLength() == 0)
            return ActionResult<lib::Array<int>>(ResponseType::commandError);

        return ActionResult<lib::Array<int>>(digraph.findShortestPath(u[0], u[1]));
    }

    ResponseType addVertex(const std::string & args) {
        std::string tmp;
        int i = 0;
        for (; i < (int) args.size(); ++i) {
            if (args[i] == ' ') break;
            tmp += args[i];
        }
        int u;
        try {
            u = std::stoi(tmp);
        } catch (std::exception &) {
            return ResponseType::commandError;
        }

        lib::DynamicArray<std::string> arr;
        arr.push("");
        for (i = i + 1; i < (int) args.size(); ++i) {
            if (args[i] == ' ') {
                arr.push("");
                continue;
            }
            arr[arr.getLength() - 1] += args[i];
        }

        lib::Array<int> res(arr.getLength());
        for (i = 0; i < arr.getLength(); ++i) {
            try {
                res[i] = std::stoi(arr[i]);
            } catch (std::exception &) {
                return ResponseType::commandError;
            }
        }

        digraph.addVertex(u, res);
        return ResponseType::Ok;
    }

    ResponseType addEdge(const std::string & args) {
        lib::Array<int> u = split(args);
        if (u.getLength() == 0)
            return ResponseType::commandError;


        digraph.addEdge(u[0], u[1]);
        return ResponseType::Ok;
    }

    ResponseType deleteVertex(const std::string & args) {
        int n;
        try {
            n = std::stoi(args);
        } catch (std::exception &) {
            return ResponseType::commandError;
        }


        digraph.deleteVertex(n);
        return ResponseType::Ok;
    }

    ResponseType deleteEdge(const std::string & args) {
        lib::Array<int> u = split(args);
        if (u.getLength() == 0)
            return ResponseType::commandError;

        digraph.deleteEdge(u[0], u[1]);
        return ResponseType::Ok;
    }

    ResponseType print(const std::string & args) {
        if (args != "") return ResponseType::commandError;

        digraph.print();

        return ResponseType::Ok;
    }

    ResponseType write(const std::string & args) {
        if (args != "") return ResponseType::commandError;

        digraph.write();

        return ResponseType::Ok;
    }

};


#endif //LAB_4_MAPCONTROLLER_H
