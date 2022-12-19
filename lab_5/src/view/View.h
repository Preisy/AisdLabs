#ifndef LAB_4_VIEW_H
#define LAB_4_VIEW_H

#include "lib.h"
#include "../controller/GraphController.h"
//#include <conio.h>
#include <stdio.h>

class View {
private:
    GraphController graphController = GraphController();
    bool autoWriting = false;

public:
    [[noreturn]] void run() {
        std::cout << "Type your command or type help;" << std::endl;
        while (true) {
            lib::DynamicArray<lib::Array<std::string, 2>> arr = ask();

            for (int i = 0; i < arr.getLength(); ++i) {
                GraphController::ResponseType responseType = GraphController::ResponseType::smthWrong;
                if (arr[i][0] == "ploh") {
                    responseType = GraphController::ResponseType::Ok;
                    std::cout << "Timofei Ilyich, isvinite, ispravlus'." << std::endl;
                    std::cin.clear();
                } else if (arr[i][0] == "megaploh") {
                    responseType = GraphController::ResponseType::Ok;
                    for (int i = 0; i < 10; ++i) {
                        std::cout << "TIMOFEI ILYICH, ISVINITE, ISPRAVLUS'!" << std::endl;
                    }
                    std::cin.clear();
                } else if (arr[i][0] == "help") {
                    responseType = GraphController::ResponseType::Ok;
                    help();
                } else if (arr[i][0] == "exit") {
                    exit(0);
                } else if (arr[i][0] == "addv") {
                    responseType = graphController.addVertex(arr[i][1]);
                } else if (arr[i][0] == "adde") {
                    responseType = graphController.addEdge(arr[i][1]);
                } else if (arr[i][0] == "path") {
                    GraphController::ActionResult<lib::Array<int>> response = graphController.findPath(arr[i][1]);
                    responseType = response.getStatus();
                    if (responseType == GraphController::ResponseType::Ok) {
                        if ((*response).getLength() == 0) {
                            std::cout << "Not Found";
                        }
                        for (int j = 0; j < (*response).getLength(); ++j) {
                            std::cout << (*response)[j];
                            if (j != (*response).getLength() - 1)
                                std::cout << ", ";
                        }
                        std::cout << std::endl;
                    }
                } else if (arr[i][0] == "spath") {
                    auto response = graphController.findShortestPath(arr[i][1]);
                    responseType = response.getStatus();
                    if (responseType == GraphController::ResponseType::Ok) {
                        if ((*response).getLength() == 0) {
                            std::cout << "Not Found";
                        }
                        for (int j = 0; j < (*response).getLength(); ++j) {
                            std::cout << (*response)[j];
                            if (j != (*response).getLength() - 1)
                                std::cout << ", ";
                        }
                        std::cout << std::endl;
                    }
                } else if (arr[i][0] == "delv") {
                    responseType = graphController.deleteVertex(arr[i][1]);
                } else if (arr[i][0] == "dele") {
                    responseType = graphController.deleteEdge(arr[i][1]);
                } else if (arr[i][0] == "print") {
                    responseType = graphController.print(arr[i][1]);
                } else if (arr[i][0] == "write") {
                    responseType = graphController.write(arr[i][1]);
                }
//                else if (arr[i][0] == "mock") {
//                    responseType = mapController.mock(arr[i][1]);
//                }
                else if (arr[i][0] == "saw") {
                    if (arr[i][1] != "") {
                        responseType = GraphController::ResponseType::commandError;
                    } else {
                        if (autoWriting) {
                            std::cout << "Auto writing disabled" << std::endl;
                        } else {
                            std::cout << "Auto writing enabled" << std::endl;
                        }
                        autoWriting = !autoWriting;
                        responseType = GraphController::ResponseType::Ok;
                    }
                }

                if (responseType == GraphController::ResponseType::inputError ||
                    responseType == GraphController::ResponseType::smthWrong) {
                    invalidInput(arr[i][0]);
                    break;
                }

                if (responseType == GraphController::ResponseType::commandError) {
                    commandProcessingError(arr[i][0]);
                    break;
                }
            }

            if (autoWriting)
                graphController.write("");
        }
    }


    lib::DynamicArray<lib::Array<std::string, 2>> ask() {
//        printf("\033[34m>>>\033[0m ");
        std::cout << "\033[34m>>> \033[36m";
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
        std::cout << "   each u is int:" << std::endl;
        std::cout << "1. addv u ...; - add vertex" << std::endl;
        std::cout << "2. adde u1 u2; - add edge" << std::endl;
        std::cout << "3. path u1 u2;" << std::endl;
        std::cout << "4. spath u1 u2;" << std::endl;
        std::cout << "5. delv u; - del vertex" << std::endl;
        std::cout << "6. dele u1 u2; - del edge" << std::endl;
        std::cout << "7. print;" << std::endl;
        std::cout << "8. write;" << std::endl;
        std::cout << "9. saw; - switch to auto writing" << std::endl;
        std::cout << std::endl;
    }

    void invalidInput(const std::string & str) {
        std::cout << "Invalid input <" << str << ">. Type help" << std::endl;
    }
    void commandProcessingError(const std::string & str) {
        std::cout << "Сommand processing error <" << str << ">. Type help" << std::endl;
    }




};


#endif //LAB_4_VIEW_H
