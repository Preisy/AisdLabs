#include <iostream>

#include "lib.h"
#include "Digraph.h"
#include "loadFromFile.h"

int main() {
    Digraph digraph = loadFromFile(R"(D:\C\labs_2_semester_C\lab_5\input.txt)");
//    Digraph digraph = loadFromFile(R"(./input.txt)");
    digraph.write();
    digraph.print();

    std::cout << std::endl;
    lib::Array<int> arr = digraph.findPath(1, 4);
    for (int i = 0; i < arr.getLength(); ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    std::cout << std::endl;
    arr = digraph.findShortestPath(2, 6);
    for (int i = 0; i < arr.getLength(); ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}


