#include "ProcessSchedulerController.h"

#include <iostream>
#include "string"

#include "View.h"
#include "Exceptions.h"

#include "ProcessSchedulerController.h"

using std::cin;
using std::string;
using std::min;

using namespace Controllers;

ProcessSchedulerController::ProcessSchedulerController(std::istream &IStream, std::ostream &OStream) :
        view(new View::Output(OStream)), in(IStream) {}

ProcessSchedulerController::~ProcessSchedulerController() {
    delete view;
}


int ProcessSchedulerController::convertToInt(const std::string &str) {
    int res = 0;
    int sign = 1;
    int i = 0;
    if (str[i] == '-') {
        ++i;
        sign = -1;
    }
    for (; i < str.size(); ++i) {
        if ('0' <= str[i] && str[i] <= '9')
            res = res * 10 + (str[i] - '0');
        else
            throw ConvertException("Incorrect input");
    }

    return res * sign;
}


bool ProcessSchedulerController::readBlock(std::string &str) {
    str = "";
    char &c = this->currentSymbol;
    while (c == ' ' || c == '\t')
        c = (char) this->in.get();
    if (c == '\n') return false;
    while (c != ' ' && c != '\t' && c != '\n') {
        str += (char) c;
        c = (char) this->in.get();
    }
    return true;
}

View::Output *ProcessSchedulerController::getView() {
    return this->view;
}
