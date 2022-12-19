#ifndef LAB_4_MAPCONTROLLER_H
#define LAB_4_MAPCONTROLLER_H

#include "lib.h"
#include "Map.h"

class MapController {
public:
    enum ResponseType {
        Ok,
        inputError,
        commandError,
        smthWrong
    };

//    template<class Data>
//    class ActionResult {
//    private:
//        Data* data = nullptr; // todo вообще оно должно течь
//        ResponseType status;
//
//    public:
//        ActionResult(Data && data, ResponseType status)
//                : data(new Data(std::move(data))), status(status) {};
//
//        explicit ActionResult(Data && data)
//                : data(new Data(std::move(data))), status(ResponseType::Ok) {};
//
//        explicit ActionResult(const ResponseType & status)
//                : status(status) {};
//
//        Data & operator*() { return *data; };
//
//        ResponseType getStatus() { return status; }
//
//        explicit operator bool() const { return status == ResponseType::Ok; };
//    };

private:
    lib::Map<int, std::string> mp;


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

    const lib::Deq<std::string> & find(const std::string & args, ResponseType & code) {
        int index = strchr(args.c_str(), ' ') - args.c_str();
        if (0 <= index && index < args.size()) {
            code = ResponseType::commandError;
            return lib::Deq<std::string>();
        }

        int n;
        try {
            n = std::stoi(args);
        } catch (std::exception &) {
            code = ResponseType::commandError;
            return lib::Deq<std::string>();
        }

        const lib::Deq<std::string> & answer = mp.find(n);

        code = ResponseType::Ok;
        return answer;
    }

    const lib::Deq<std::string> & specialFind(const std::string & args, ResponseType & code) {
        int index = strchr(args.c_str(), ' ') - args.c_str();
        if (0 <= index && index < args.size()) {
            code = ResponseType::commandError;
            return lib::Deq<std::string>();
        }

        int n;
        try {
            n = std::stoi(args);
        } catch (std::exception &) {
            code = ResponseType::commandError;
            return lib::Deq<std::string>();
        }

        auto res = mp.specialFind(n);
        if (res == nullptr) {
            code = ResponseType::Ok;
            return lib::Deq<std::string>();
        } else {
            const lib::Deq<std::string> & answer = *res;

            code = ResponseType::Ok;
            return answer;
        }
    }

    ResponseType del(const std::string & args) {
//        int index = strchr(args.c_str(), ' ') - args.c_str();
//        if (0 <= index && index < args.size())
//            return ResponseType::commandError;

        std::string key;
        std::string version;
        int i = 0;
        for (; i < args.size(); ++i) {
            if (args[i] == ' ')
                break;
            key += args[i];
        }
        ++i;
        for (; i < args.size(); ++i) {
            if (args[i] == ' ') return ResponseType::commandError;
            version += args[i];
        }

        int k;
        try {
            k = std::stoi(key);
        } catch (std::exception &) {
            return ResponseType::commandError;
        }
        if (version == "") {
            mp.remove(k);
        } else {
            int v;
            try {
                v = std::stoi(version);
            } catch (std::exception &) {
                return ResponseType::commandError;
            }
            mp.remove(k, v);
        }

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
