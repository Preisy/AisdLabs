#ifndef LAB_3_SAFEDELETE_H
#define LAB_3_SAFEDELETE_H

namespace lib {
#define safeDelete(x) \
    do { \
        if ((x) != NULL) {  \
            delete (x);   \
            (x) = NULL; \
        } \
    } while (false)
//    template<class T>
////    bool safeDelete(T* el) {
//    bool safeDelete(T*& el) {
//        if (el != nullptr) {
//            delete el;
//            el = nullptr;
//            return true;
//        } else {
//            return false;
//        }
//    }
}

#endif //LAB_3_SAFEDELETE_H
