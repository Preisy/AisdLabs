#ifndef lab_2_ProcessSchedulerController_h
#define lab_2_ProcessSchedulerController_h

#include "Controllers/IController.h"
#include "View.h"

namespace Controllers {

    class ProcessSchedulerController : public IController {
    public:
        ProcessSchedulerController(std::istream &IStream, std::ostream &OStream);
        ~ProcessSchedulerController();

    protected:
        int convertToInt(const std::string &);

        bool readBlock(std::string &);

    private:
        std::istream &in;
        char currentSymbol = ' ';

    protected:
        View::Output* getView();

    protected:
        View::Output* view;
    };

}
#endif