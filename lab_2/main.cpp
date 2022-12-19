#include <iostream>

#include "Controllers.h"
#include "Exceptions.h"

bool isEqual(const char *str1, const char *str2) {
    for (int i = 0;; ++i) {
        if (str1[i] == '\0' && str2[i] == '\0') return true;
        if (str1[i] == '\0' || str2[i] == '\0') return false;
        if (str1[i] != str2[i]) return false;
    }
}

bool isFlag(const char *str) {
    return str[0] == '-';
}


int main(int argc, char *argv[]) {

    std::ifstream fin;
    std::ofstream fout;
    bool istreamFlag = false;
    bool ostreamFlag = false;

    for (int i = 1; i < argc; ++i) {
        if (isEqual(argv[i], (char *) "-in")) {
            if (i + 1 >= argc || isFlag(argv[i + 1])) throw StartupException("Incorrect flag " + std::string(argv[i]));
            const char *filename = argv[++i];
            fin = std::ifstream(filename, std::ios_base::in);
            if (!fin.is_open()) throw StartupException("File " + std::string(filename) + " not found");
            istreamFlag = true;
        }
        if (isEqual(argv[i], (char *) "-out")) {
            if (i + 1 >= argc || isFlag(argv[i + 1])) throw StartupException("Incorrect flag " + std::string(argv[i]));
            const char *filename = argv[++i];
            fout = std::ofstream(filename, std::ios_base::app);
//            fout = std::ofstream(filename);
            if (!fout.is_open()) throw StartupException("File " + std::string(filename) + " not found");

            ostreamFlag = true;
        }
    }


    std::istream &in = istreamFlag ? fin : std::cin;
    std::ostream &out = ostreamFlag ? fout : std::cout;

    Controllers::IController *pc = new Controllers::RoundRobinController(in, out);
    pc->request();


    delete pc;

    return 0;
}

