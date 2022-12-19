#include "iostream"

int main() {
    for (int i = 1; i < 256; ++i) {
        std::cout << i << ": " << (char) i << " ";
        if (i % 20 == 0) std::cout << std::endl;
    }

    return 0;
}