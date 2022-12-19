#include "RoundRobinService.h"
#include "Lib.h"
#include "Entities.h"

using namespace Services;

std::vector<int>* RoundRobinService::distributeProcess(const std::vector<Entities::ProcessModel> & inp) const {
    auto* history = new std::vector<int>();

    lib::IQueue<Entities::ProcessModel> * q = new lib::QueueList<Entities::ProcessModel>();

    std::vector<Entities::ProcessModel>::const_iterator it = inp.begin();
    for (int currentTime = 0; !q->empty() || it != inp.end(); ++currentTime) {
        if (it != inp.end() && it->getTc() <= currentTime)
            q->push(*(it++));

        if (q->empty()) {
            history->push_back(-1);
            continue;
        }
        Entities::ProcessModel top = q->pop();
        for (int i = 0; i < std::min(top.getTe(), this->getTimeQuantum()); ++i) {
            history->push_back(top.getId());
            ++currentTime;
        }
        if (it != inp.end() && it->getTc() <= currentTime)
            q->push(*(it++));
        if (top.getTe() > this->getTimeQuantum()) {
            top.setTe(top.getTe() - this->getTimeQuantum());
            q->push(top);
        }
    }
    delete q;

    return history;
}