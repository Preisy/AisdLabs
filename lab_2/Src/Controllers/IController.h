#ifndef lab_2_IController_h
#define lab_2_IController_h

namespace Controllers {

    class IController {
    public:
        virtual void request() = 0;

        virtual ~IController() = default;
    };

}
#endif