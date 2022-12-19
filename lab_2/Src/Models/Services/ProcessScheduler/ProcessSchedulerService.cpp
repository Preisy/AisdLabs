#include "Entities.h"
#include "Lib.h"

#include "ProcessSchedulerService.h"
#include "Exceptions.h"
#include "iostream"

using namespace Services;

//std::vector<int> ProcessSchedulerService::roundRobin(const std::vector<ProcessModel> &inp) const

const int &ProcessSchedulerService::getTimeQuantum() const { return this->timeQuantum; }

void ProcessSchedulerService::setTimeQuantum(int value) {
    if (value <= 0) throw ConvertException("Time quantum must be greater than zero");
    this->timeQuantum = value;
}
