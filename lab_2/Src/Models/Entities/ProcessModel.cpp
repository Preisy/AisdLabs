#include "ProcessModel.h"
#include "Exceptions.h"

#include <iostream>

using namespace Entities;

ProcessModel::ProcessModel(const int &id, const int &tc, const int &te) : _id(id), _tc(tc), _te(te) {}

ProcessModel::ProcessModel(const std::string &str) {
    int i = 0;
    this->_id = this->convertToInt(str, i);
    if (this->_id < 0) throw ConvertException("Value should be greater than or equal to than zero");
    this->_tc = this->convertToInt(str, ++i);
    if (this->_tc < 0) throw ConvertException("Value should be greater than or equal to than zero");
    this->_te = this->convertToInt(str, ++i);
    if (this->_te <= 0) throw ConvertException("Value should be greater than zero");
}

int ProcessModel::convertToInt(std::string str, int & i) {
    if (str.length() == 0) throw ConvertException("Incorrect input");
    int sign = 1;
    if (str[i] == '-') {
        ++i;
        sign = -1;
    }
    int res = 0;
    for (; i < str.length(); ++i) {
        if ('0' <= str[i] && str[i] <= '9')
            res = res * 10 + (str[i] - '0');
        else if (str[i] == '/')
            break;
        else
            throw ConvertException("Incorrect input");
    }
    return res * sign;
}


const int & ProcessModel::getId() const { return this->_id; }

const int & ProcessModel::getTc() const { return this->_tc; }

const int & ProcessModel::getTe() const { return this->_te; }

void ProcessModel::setTe(const int & te) {
    if (te <= 0) throw ConvertException("Value should be greater than zero");
    this->_te = te;
}

std::ostream &operator<<(std::ostream &os, const ProcessModel &p) {
    return os << p.getId() << " "
              << p.getTc() << " "
              << p.getTe();
}