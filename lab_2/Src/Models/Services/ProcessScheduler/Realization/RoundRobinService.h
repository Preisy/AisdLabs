#ifndef LAB_2_ROUNDROBINSERVICE_H
#define LAB_2_ROUNDROBINSERVICE_H

#include "../ProcessSchedulerService.h"
#include "Entities.h"

namespace Services {
    class RoundRobinService : public ProcessSchedulerService {
        std::vector<int>* distributeProcess(const std::vector<Entities::ProcessModel> &) const override;
    };

}


#endif //LAB_2_ROUNDROBINSERVICE_H
