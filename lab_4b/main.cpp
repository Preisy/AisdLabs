#include <iostream>
#include <time.h>

#include "lib.h"


//8829, 1394, 8623, 8512, 4842, 9579, 711, 2683, 2734, 3383
//del 8829;

int main() {
    lib::AVLMap<int, int> mp;

//    int els[] = {62, 69, 22, 8, 31, 67, 13, 88, 80, 46};
// del 22; del 62;
//    int els[] = {65, 40, 73, 94, 43, 1, 11, 29, 84, 25};
//    mp.remove(29);
//    mp.remove(84);
//    mp.remove(1);
//    mp.remove(25);
//    int els[] = {65, 40, 84, 11, 43, 73, 94, 1, 25};
//    int els[] = {65, 40, 94, 11, 43, 73, 25};


    int els[] = {73, 32, 75, 24, 37, 74, 100, 4, 26};



    int n = sizeof (els) / sizeof (els[0]);
    for (int i = 0; i < n; ++i) {
        mp.add({els[i], 0});
        if (!mp.check()) std::cout << "Alert" << std::endl;
    }
    mp.write();


//    mp.remove(37);
    auto res = mp.specialFind(32);
    if (res != nullptr) {
        std::cout << *res << std::endl;
    } else {
        std::cout << "ss" << std::endl;
    }

    mp.write();

//    add 38; add 52; add 45; add 96; add 72; add 22; add 19; add 70; add 57; add 40; del 22; write;




//    lib::AVLMap<int, int> mp;
//
//    srand(time(0));
//
////    int arr[] = {7210,9019,7304,3492,2282,2181,2286,5442,9915,592,7219,625,6997,4981,6138,183,7806,1297,1055,435,9777,5542,4089,1817,8382,4560};
////    int arr[] = {3492, 2282, 2181, 2286, 592, 625, 4981, 183, 1297, 1055, 435, 4089, 1817, 4560};
////    int arr[] = {3492, 2282, 2181, 592, 625};
////    int arr[] = {2282, 2181, 3492, 592, 625};
////    int arr[] = {8476, 8049, 5102, 2993, 7969, 1587, 1794};
////    int arr[] = {8049, 5102, 8476, 2993, 7969, 1587, 1794};
////    int arr[] = {5102, 2993, 8049, 1587, 7969, 8476, 1794};
////    int arr[] = {5102, 2993, 8049, 1587, 7969, 8476, 1794};
////    int n = sizeof(arr) / sizeof(arr[0]);
//
//    int n = 1000;
//    lib::LinkedList<int> arr;
//    for (int i = 0; i < n; ++i) {
//        arr.push( + rand() % 10000);
//    }
//
//    for (int i = 0; i < n; ++i) {
//        std::cout << arr[i] << ", ";
//        mp.add({arr[i], 0});
//        if (!mp.check()) std::cout << "Alert" << std::endl;
//    }
//
//    std::cout << std::endl;
//    std::cout << std::endl;
//    std::cout << std::endl;
//    std::cout << std::endl;
//    std::cout << std::endl;
//    std::cout << std::endl;
//    int i = 0;
//    for (; ; ) {
//        if (i >= arr.getLength())
//            break;
//        int index = rand() % arr.getLength();
//        std::cout << arr[index] << ", " << std::flush;
//        mp.remove(arr[index]);
//        arr.removeAt(index);
//        if (!mp.check()) std::cout << "Alert" << std::endl;
//    }
//
//
////    mp.write();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
