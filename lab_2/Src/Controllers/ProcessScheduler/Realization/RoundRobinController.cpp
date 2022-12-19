#include "string.h"

#include "RoundRobinController.h"
#include "Services.h"
#include "Entities.h"

using namespace Controllers;

RoundRobinController::RoundRobinController(std::istream &IStream, std::ostream &OStream)
        : ProcessSchedulerController(IStream, OStream),
        service(new Services::RoundRobinService()) {}

RoundRobinController::~RoundRobinController() { // todo почему он предлагает написать деструктор noexcept?
    delete service;
}

void RoundRobinController::request() {
    std::string str;
    this->readBlock(str);
    int timeQuantum = this->convertToInt(str);

    auto inp = std::vector<Entities::ProcessModel>();
    bool request;
    do {
        request = this->readBlock(str);
        if (request) {
            Entities::ProcessModel process = Entities::ProcessModel(str);
            inp.push_back(process);
        }
    } while (request);

    this->service->setTimeQuantum(timeQuantum);
    std::vector<int>* v = this->service->distributeProcess(inp);
    // todo или лучше возвращать на стеке и использовать семантику перемещений?

    this->view->setOutputData(v);
    this->view->print();

    delete v;
}

Services::ProcessSchedulerService *RoundRobinController::getService() {
    return this->service;
}
