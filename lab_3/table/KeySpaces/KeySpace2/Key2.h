#ifndef LAB_3_KEY2_H
#define LAB_3_KEY2_H

#include "iostream"
#include <string>
#include "KeySpaces/IKey.h"

class Key2 : public IKey {
private:
    std::string key;
public:
    std::string toString() const override {
        return key;
    }

public:
    Key2(const Key2 & key2) : key(key2.key) {};
public:
    Key2(const IKey* key2) {
        const Key2* k = dynamic_cast<const Key2*>(key2);
        if (k == nullptr)
            throw KeyException("Error in Key2::Key2()\n"
                               "wtf: Cannot casting IKey to Key2");
        key = k->key;
    };

public:
    explicit Key2(const std::string & key)
            : key(key) {};

    bool isEqual(const IKey* key) const override {
        auto k = dynamic_cast<const Key2*>(key);
        if (k != nullptr)
            return this->key == k->key;
        else
            return false;
    }
};

#endif //LAB_3_KEY2_H
