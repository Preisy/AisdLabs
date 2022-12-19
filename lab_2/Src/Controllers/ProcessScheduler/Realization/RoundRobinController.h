#ifndef lab_2_RoundRobin_h
#define lab_2_RoundRobin_h
#include "../ProcessSchedulerController.h"

#include "Services.h"

namespace Controllers {

    class RoundRobinController : public ProcessSchedulerController {
    public:
        RoundRobinController(std::istream &IStream, std::ostream &OStream);

        ~RoundRobinController();

        void request() override;

    protected:
        Services::ProcessSchedulerService* getService();

    private:
        Services::ProcessSchedulerService* service;

    };

}
#endif