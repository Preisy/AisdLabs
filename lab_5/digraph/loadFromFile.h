#ifndef LAB_5_LOADFROMFILE_H
#define LAB_5_LOADFROMFILE_H

#include "Digraph.h"
#include "sstream"

Digraph loadFromFile(const std::string & fileName) {
    std::ifstream fin(fileName, std::ios_base::in);
    if (!fin.is_open())
        return {};

    Digraph digraph;
    int n;
    std::string str;
    while(getline(fin, str, '\n')) {
        std::stringstream sin(str);
        lib::DynamicArray<int> tmp;
        int u;
        sin >> u;
        int n;
        while(sin >> n) {
            tmp.push(n);
        }
        lib::Array<int> arr(tmp.getLength());
        for (int i = 0; i < tmp.getLength(); ++i)
            arr[i] = tmp[i];
        digraph.addVertex(u, arr);
    }

    return digraph;
}



#endif //LAB_5_LOADFROMFILE_H
