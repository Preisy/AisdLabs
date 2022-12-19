#include <iostream>

#include "lib.h"
#include "getMapFromFile.h"



int main() {
//    auto mp1 = getMapFromFile(R"(D:\C\labs_2_semester_C\lab_4\input.txt)");
//    if (mp1)
//        (*mp1).print();

//    auto mp2 = lib::Map<int, std::string>();
////    double els[] = {7, 3, 12, 9, 10, 8, 19, 1, 2, 14, 16, 25, 30, 15, 17, 18, 20};
////    double els[] = {7, 3, 12, 9, 10, 8, 19, 1, 2, 14, 16, 25, 30, 15, 17, 18, 20};
//    double els[] = {7, 3, 12, 9, 10, 8, 19, 1, 2, 14, 16, 25, 30, 15, 17, 18, 20, 13 };
////    double els[] = {4, 1, 20, 15, 18, 17, 16};
////    double els[] = {1, 25, 4, 8};
////add 4; add 1; add 20; add 15; add 18; add 17; add 16; print;
////add 7 a; add 3 a; add 12 a; add 9 a; add 10 a; add 8 a; add 19 a; add 1 a; add 2 a; add 14 a; add 16 a; add 25 a; print;
////    double els[] = {4, 1, 20, 15};
//    int n = sizeof (els) / sizeof (els[0]);
//    for (int i = 0; i < n; ++i) {
//        mp2.add({els[i], std::to_string(i)});
////        std::cout << els[i] << std::endl << i << std::endl;
//    }
//    mp2.print();
//    mp2.write();
//
//
//
////    std::cout << mp2.specialFind(17) << std::endl;
//
////    mp2.specialTreeTraversal(7);
////    mp2.specialTreeTraversal();
//
////    mp2.traversal();
//    int key = 12;
//    std::string a = "1236";
//    int index = strchr(a.c_str(), '0') - a.c_str();
//    mp2.remove(key);
//    std::cout << std::endl << std::endl << std::endl;
//    std::cout << "remove " << key << std::endl;
//    mp2.print();
//    mp2.traversal();

//    for (int i = 0; i < n; ++i) {
//        if (i == n - 1)
//            int a = 0;
//        tree.remove(els[i]);
//        if (!tree.check()) std::cout << "don't correct" << std::endl;
//    }

    auto mp = lib::Map<int, std::string>();
//    int els[] = {7, 3, 12, 9, 10, 8, 19, 1, 2, 14, 16, 25};
//    int els[] = {8, 3, 14, 1, 9, 19, 2, 10, 16, 25};
//    int els[] = {8, 3, 14, 1, 9, 19, 2, 10, 16, 25};
//    int els[] = {7, 1, 2, 3, 14, 9, 19, 8, 10, 16, 18, 25, 11};
    int els[] = {7, 3, 12, 1, 9, 19, 0, 2, 8, 10, 14, 25, 11, 16};
//    int els[] = {7, 3, 12, 1, 19, 9, 2, 0, 25, 14, 11, 8, 16};
//    int els[] = {7, 3, 12, 1, 9, 19, 0, 2, 8, 10};
//    int els[] = {7, 3, 12, 14};
    int n = sizeof (els) / sizeof (els[0]);
    for (int i = 0; i < n; ++i) {
        mp.add({els[i], "a"});
    }

    mp.add({3, "b"});
//    mp.remove(12);
//    mp.remove(7);
    mp.write();
//    mp.remove(19);
//    mp.remove(10);
//    mp.remove(12);
//    mp.remove(7);

    mp.specialFind(12);


    mp.write();


//    system("dot tmp.dot | neato -n -Tpng -o tree.png");

    return 0;
}
