#include "iostream"

#include "lib.h"

template<class T>
class A {
    T el = T();

public:
    void foo(T& a) {
        std::cout << a << std::endl;
    }
};

int main() {
    A<const int*> a;
    int* b = new int(2);
    a.foo(b);


    return 0;
}