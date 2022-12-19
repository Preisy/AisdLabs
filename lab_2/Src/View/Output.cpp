#include "Output.h"
#include "algorithm"
#include "fstream"
#include "vector"
#include "stdio.h"

using namespace View;

Output::Output(std::ostream & OStream)
        : out(OStream) {}


void Output::print() {
    std::vector<int> &arr = *(this->outputData);
    int trNumber = *std::max_element(arr.begin(), arr.end());

    this->out << "ID ";
    for (int i = 0; i < arr.size(); ++i)
        this->out << i << " ";
    this->out << std::endl;

    for (int i = 0; i <= trNumber; ++i) {
        this->out << i << "  ";
        for (int j = 0; j < arr.size(); ++j) {
            if (arr[j] == i)
                this->out << "* ";
            else
                this->out << "  ";
            for (int k = j; k >= 10; k = k / 10)
                this->out << " ";
        }
        this->out << std::endl;
    }

}

void Output::pushOutputData(const int &data) {
    this->outputData->push_back(data);
}

void Output::setOutputData(std::vector<int> * data) noexcept {
    this->outputData = data;
}
