#include <iostream>
#include <fstream>

#include "lib.h"
#include "getMapFromFile.h"


bool isLetter(char c);

int main() {
    lib::Map<std::string, int> mp;

    std::ifstream fin(R"(D:\C\labs_2_semester_C\lab_4\BIG_FILE.txt)", std::ios_base::in);
    std::string str;
    while (fin >> str) {
        std::string buf;
        for (int i = 0; i < str.size(); ++i) {
            if (isLetter(str[i])) {
                buf += std::tolower(str[i]);
            } else {
                if (!buf.empty() && !mp.add({buf, 1}))
                    ++mp.find(buf);
                buf = "";
            }
        }
        if (!buf.empty() && !mp.add({buf, 1}))
            ++mp.find(buf);
    }


    auto arr = mp.getSortedArray();
    for (int i = 0; i < arr.getLength(); ++i) {
        std::cout << arr[i].first << ": " << arr[i].second << std::endl;
    }

    return 0;
}

bool isLetter(char c) {
    return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

