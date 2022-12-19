#pragma once
#include "vector"
#include "Entities.h"

namespace Services {

    class ProcessSchedulerService {
    public:
        virtual std::vector<int>* distributeProcess(const std::vector<Entities::ProcessModel> &) const = 0;

        virtual ~ProcessSchedulerService() = default;

    public:
        const int &getTimeQuantum() const;

        void setTimeQuantum(int);


    private:
        int timeQuantum;
    };
}