#pragma once

#include <iostream>

namespace Entities {

    class ProcessModel {
    public:
        ProcessModel(const int &, const int &, const int &);

        explicit ProcessModel(const std::string &);

    private:
        int convertToInt(std::string, int &);

    private:
        int _id;
        int _tc;
        int _te;

    public:
        const int &getId() const;

        const int &getTc() const;

        const int &getTe() const;

        void setTe(const int &);
    };

}