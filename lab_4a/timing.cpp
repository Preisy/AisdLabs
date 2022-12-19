#include "Map.h"
//#include "time.h"
#include <ctime>
#include <cstdlib>
#include "limits.h"

#include "iostream"

int timeAdd(lib::Map<int, std::string> & mp);

int main() {

    int arr[10] = {0};

    srand((time(NULL)));
    for (int size = 1000; size < 100000; size+=1000) {
        double  timeLocal = 0;
        for (int i = 0; i < 10; ++i) {
            lib::Map<int, std::string> mp;
            for (int j = 0; j < size; ++j) mp.add({rand(), ""});
            timeLocal += timeAdd(mp);
        }
        std::cout << size << ";" << timeLocal << ";" << std::endl;
    }
}

int timeAdd(lib::Map<int, std::string> & mp) {
    int arr[100];
    for (int i = 0; i < 100; ++i) {
        arr[i] = rand();
    }
    clock_t start = clock();
    for (int j = 0; j < 100; ++j) {
//        mp.find(arr[j]);
//        mp.add({arr[j], ""});
        mp.remove(arr[j]);
    }
    return (clock() - start);
}


