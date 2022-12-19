#ifndef LAB_3_VIEW_H
#define LAB_3_VIEW_H

#include <iostream>
#include <limits>
#include "../controller/TableController.h"
#include "lib.h"
#include "Table.h"

class View {
private:
    TableController tableController;
    lib::Array<std::string, 5> commands;

//    find a a; find a a 2; del a a; del a a; del a a 2; print; add a a;
public:
    View() {
        commands[0] = "add";
        commands[1] = "find";
        commands[2] = "del";
        commands[3] = "print";
        commands[4] = "pks2";
    }


    [[noreturn]] void run() {
        std::cout << "Type your command or type help;" << std::endl;
        while (true) {
            lib::Array<std::string, 2> arr = ask();

            TableController::ResponseType responseType;
            if (arr[0] == commands[0]) {
                responseType = tableController.add(arr[1]);
            } else if (arr[0] == commands[1]) {
                auto it = tableController.find(arr[1]);
                responseType = it.getStatus();
                if (responseType == TableController::ResponseType::Ok) {
                    if ((*it).isEnded() && (*it).isAtStart()) {
                        std::cout << "Not found" << std::endl;
                    }
                    while (!(*it).isEnded()) {
                        std::cout << (**it).getKey().toString() <<
                                  "_" << (**it).getVersion() <<
                                  ": " << (**it).getData() << std::endl;
                        ++(*it);
                    }
                }
            } else if (arr[0] == commands[2]) {
                responseType = tableController.del(arr[1]);
            } else if (arr[0] == commands[3]) {
                responseType = tableController.print(arr[1]);
                char c = std::cin.get();
                int a = 0;
            } else if (arr[0] == commands[4]) {
                responseType = tableController.printKeySpace2Array(arr[1]);
                char c = std::cin.get();
            } else {
                exit(-5);
            }

            if (responseType == TableController::ResponseType::inputError) {
                invalidInput(arr[0]);
                continue;
            }
            if (responseType == TableController::ResponseType::commandError) {
                commandProcessingError(arr[0]);
                continue;
            }
        }

    }

private:
    lib::Array<std::string, 2> ask() {
        static bool tabFlag = true;
        if (tabFlag)
			std::cout << ">>> ";
        lib::Array<std::string, 2> res;

//        while (std::cin.get() == '>');
//        std::cin.get();
        res[0] = getLine();
        if (res[0] == "") {
            std::string tmp;
            getline(std::cin, tmp, '\n');

            invalidInput(res[0]);
            return ask();
        }
//        getline(std::cin, res[0], ' ');
//        if (!getline(std::cin, res[0], ' ')) {
//            dontCorrectInput(res[0]);
//            return ask();
//        }
        if (res[0] == "ploh") { // todo harosh
            std::cout << "Timofei Ilyich, isvinite, ispravlus'." << std::endl;
            std::cin.get();
            return ask();
        }else if (res[0] == "megaploh") {
            for (int i = 0; i < 10; ++i) {
                std::cout << "TIMOFEI ILYICH, ISVINITE, ISPRAVLUS'!" << std::endl;
            }
            std::cin.get();
            return ask();
        } else if (res[0] == "help") {
            help();
            std::cin.get();
            return ask();
        } else if (res[0] == "exit") {
            exit(0);
        } else if (res[0] == "print") {
            res[0] = "print";
            return res;
        } else if (res[0] == "pks2") {
            res[0] = "pks2";
            return res;
        }

        bool flag = false;
        for (int i = 0; i < commands.getLength(); ++i) {
            if (res[0] == commands[i]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            std::string tmp;
            getline(std::cin, tmp, '\n');
            invalidInput(res[0]);
            return ask();
        }

//        getline(std::cin, res[1], ';');
//        res[1] = getLine();
        getline(std::cin, res[1], ';');
        char c = std::cin.get();
        if (c == ' ')
            tabFlag = false;
        else
            tabFlag = true;
//        while (c == ' ') {
//            c = std::cin.get();
//            if (c != ' ' && c != '\n') {
//                std::cin.seekg(-1, std::ios::cur);
//                tabFlag = true;
//                break;
//            } if (c == '\n') {
//                tabFlag = true;
//                break;
//            } else {
//                tabFlag = false;
//            }
//        }


        return res;
    }

    std::string getLine() {
        std::string res;
        char c = std::cin.get();
        while (c != ' ' && c != ';') {
            if (c == '\n') {
                return "";
            }
            res += c;
            c = std::cin.get();
        }
        return res;
    }

    void help() {
        std::cout << "Examples of commands:" << std::endl;
        std::cout << "0. help;" << std::endl;
        std::cout << "0. exit;" << std::endl;
        std::cout << "1. add key1 key2 key3: data;" << std::endl;
        std::cout << "2. find key1 key2 key3;" << std::endl;
        std::cout << "  2.1. Each key may by null (-)" << std::endl;
        std::cout << "  2.2. find - key2 key3 1; You can type item version" << std::endl;
        std::cout << "3. del key1 key2 key3;" << std::endl;
        std::cout << "  3.1. Each key may by null (-)" << std::endl;
        std::cout << "  3.2. del key1 key2 key3 1; You can type version, but key each key must be not null;" << std::endl;
        std::cout << "4. print;" << std::endl;
        std::cout << "5. pks2;" << std::endl;
        std::cout << std::endl;
        std::cout << "You can try to enter example command:" << std::endl;
        std::cout << "add a a: 23; add a a: 24; add a bbdasdf: 25; add a b: 26; add b c: 27; print; del - b; print; find a -;" << std::endl;
        std::cout << "Equals hashes:" << std::endl;
        std::cout << "add aa key: 28; add jt key: 29; add aa key: 30;" << std::endl;
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


#endif //LAB_3_VIEW_H
