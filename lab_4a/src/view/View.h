#ifndef LAB_4_VIEW_H
#define LAB_4_VIEW_H

#include "lib.h"
#include "../controller/MapController.h"

class View {
private:
    MapController mapController;

public:
    [[noreturn]] void run() {
        std::cout << "Type your command or type help;" << std::endl;
        while (true) {
            lib::DynamicArray<lib::Array<std::string, 2>> arr = ask();

            for (int i = 0; i < arr.getLength(); ++i) {
                MapController::ResponseType responseType = MapController::ResponseType::smthWrong;
                if (arr[i][0] == "ploh") {
                    responseType = MapController::ResponseType::Ok;
                    std::cout << "Timofei Ilyich, isvinite, ispravlus'." << std::endl;
                    std::cin.clear();
                } else if (arr[i][0] == "megaploh") {
                    responseType = MapController::ResponseType::Ok;
                    for (int i = 0; i < 10; ++i) {
                        std::cout << "TIMOFEI ILYICH, ISVINITE, ISPRAVLUS'!" << std::endl;
                    }
                    std::cin.clear();
                } else if (arr[i][0] == "help") {
                    responseType = MapController::ResponseType::Ok;
                    help();
                } else if (arr[i][0] == "exit") {
                    exit(0);
                } else if (arr[i][0] == "add") {
                    responseType = mapController.add(arr[i][1]);
                } else if (arr[i][0] == "stt") {
                    responseType = mapController.specialTreeTraversal(arr[i][1]);
                } else if (arr[i][0] == "find") {
                    const lib::Deq<std::string> & response = mapController.find(arr[i][1], responseType);
                    if (responseType == MapController::ResponseType::Ok) {
                        if (response.empty()) {
                            std::cout << "Not Found" << std::endl;
                        } else {
                            for (auto it = response.begin(); it != response.end(); ++it) {
                                std::cout << (*it) << "; ";
                            }
                            std::cout << std::endl;
                        }
                    }
                } else if (arr[i][0] == "sfind") {
                    const lib::Deq<std::string> & response = mapController.specialFind(arr[i][1], responseType);
                    if (responseType == MapController::ResponseType::Ok) {
                        if (response.empty()) {
                            std::cout << "Not Found" << std::endl;
                        } else {
                            for (auto it = response.begin(); it != response.end(); ++it) {
                                std::cout << (*it) << "; ";
                            }
                            std::cout << std::endl;
                        }
                    }
                } else if (arr[i][0] == "del") {
                    responseType = mapController.del(arr[i][1]);
                } else if (arr[i][0] == "print") {
                    responseType = mapController.print(arr[i][1]);
                } else if (arr[i][0] == "write") {
                    responseType = mapController.write(arr[i][1]);
                }

                if (responseType == MapController::ResponseType::inputError ||
                    responseType == MapController::ResponseType::smthWrong) {
                    invalidInput(arr[i][0]);
                    break;
                }

                if (responseType == MapController::ResponseType::commandError) {
                    commandProcessingError(arr[i][0]);
                    break;
                }
            }


        }
    }


    lib::DynamicArray<lib::Array<std::string, 2>> ask() {
        std::cout << "\033[34m>>> \033[36m";

//std::cout << ">>> ";
        lib::DynamicArray<lib::Array<std::string, 2>> arr;
        std::string ans = getLine();
		std::cout << "\033[0m";
        while (ans[ans.size() - 1] != '\n') {
            lib::Array<std::string, 2> tmp = split(ans);
            arr.push(tmp);
            ans = getLine();
        }

        if (ans.size() != 1)
            arr.push(split(ans.substr(0, ans.size() - 1)));

        return arr;
    }

    lib::Array<std::string, 2> split(const std::string & ans) {
        lib::Array<std::string, 2> tmp;
        int i = 0;
        for (; i < ans.size(); ++i) {
            if (ans[i] == ' ')
                break;
            else
                tmp[0] += ans[i];
        }
        for (i += 1; i < ans.size(); ++i) {
            tmp[1] += ans[i];
        }
        return tmp;
    }


    std::string getLine() {
        std::string res;
        char c = std::cin.get();
        while (c == ' ') {c = std::cin.get();};
        while (c != ';') {
            res += c;
            if (c == '\n') {
                break;
            }
            c = std::cin.get();
        }
        return res;
    }

    void help() {
        std::cout << "Examples of commands:" << std::endl;
        std::cout << "0. help;" << std::endl;
        std::cout << "0. exit;" << std::endl;
        std::cout << "1. add 12 value;" << std::endl;
        std::cout << "2. stt 12;" << std::endl;
        std::cout << "  2.1 stt;" << std::endl;
        std::cout << "3. find 12;" << std::endl;
        std::cout << "4. sfind 12;" << std::endl;
        std::cout << "5. del 12;" << std::endl;
        std::cout << "  5.1 del 12 0;" << std::endl;
        std::cout << "6. print;" << std::endl;
        std::cout << "7. write;" << std::endl;
        std::cout << std::endl;
        std::cout << "You can try to enter example command:" << std::endl;
        std::cout << "add 7 a; add 3 b; add 12 c; add 9 d; add 10 e; add 8 f; add 19 g; add 1 h; add 2 i; add 14 j; add 16 k; add 25 l; add 11 ks; print;" << std::endl;
    }

    void invalidInput(const std::string & str) {
//        std::cin.clear();
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input <" << str << ">. Type help" << std::endl;
    }
    void commandProcessingError(const std::string & str) {
//        std::cin.clear();
//        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Сommand processing error <" << str << ">. Type help" << std::endl;
    }




};


#endif //LAB_4_VIEW_H
