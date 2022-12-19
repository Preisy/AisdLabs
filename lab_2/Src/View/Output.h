#pragma once

#include <iostream>
#include <fstream>
#include "vector"

namespace View {

    class Output {
    public:
        explicit Output(std::ostream &OStream);

        void print();

        void pushOutputData(const int &);

        void setOutputData(std::vector<int> *) noexcept;


    private:
        std::ostream &out;

        std::vector<int>* outputData;
    };

}